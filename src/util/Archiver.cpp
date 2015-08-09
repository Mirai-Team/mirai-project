////////////////////////////////////////////////////////////
//
// MiraiProject
// Copyright (C) 2014-2015 CORTIER Benoît (benoit.cortier@gmail.com),
//                         BOULMIER Jérôme (jerome.boulmier@outlook.fr)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the
// use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
// you must not claim that you wrote the original software.
// If you use this software in a product, an acknowledgment
// in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
// and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

#include <fstream>
#include <functional>
#include <string>

#include "MiraiProject/util/Archiver.hpp"
#include "MiraiProject/util/FilesUtilities.hpp"
#include "MiraiProject/util/StringUtilities.hpp"

mp::Archiver::Archiver()
    : fileNames_ {}
    , headerLength_ {8}
{}

void mp::Archiver::createFile(const std::string& outputFile,
    const std::string& directory,
    const std::function<void(void* data, size_t size)>& encryption,
    const std::function<void(void* data, size_t size)>& compression)
{
    std::fstream output(outputFile, std::ios::in | std::ios::out | std::ios::binary | std::ios::trunc);
    if (!output)
        throw std::system_error(errno, std::system_category());

    if (!boost::filesystem::exists(directory))
        throw std::system_error(errno, std::system_category());

    if (!boost::filesystem::is_directory(directory))
        throw std::system_error(ENOTDIR, std::system_category());

    fileNames_ = filesUtilities::listFiles(boost::filesystem::path(directory), true);

    for (auto& fileName : fileNames_)
        fileName.erase(fileName.find(directory), directory.length());

    std::sort(fileNames_.begin(), fileNames_.end(), priv::stringComparaison<std::string>);

    #ifdef _WIN32

        std::string temp { directory };
        for (auto* fileName : fileNames_)
            mp::filesUtilities::convertToUnixFilePath(&fileName);

        mp::filesUtilities::convertToUnixFilePath(&temp);

        writeHeader(&output, temp);
        writeBody(&output, temp);
    #else
        writeHeader(&output, directory);
        writeBody(&output, directory, encryption, compression);
    #endif


}

void mp::Archiver::writeHeader(std::fstream* output,
    const std::string& directory)
{
    const unsigned int fileCount = static_cast<unsigned int>(fileNames_.size());
    unsigned int fileSize, fileOffset = 0, fileNameLen;

    output->seekg(4, std::ios::beg);
    // Write the number of files which are encrypted.
    output->write(reinterpret_cast<const char*>(&fileCount), sizeof(unsigned int));

    for (unsigned int i = fileCount; i-- ; ) {
        fileNameLen = static_cast<int>(fileNames_[i].size());
        output->write(reinterpret_cast<char*>(&fileNameLen), sizeof(unsigned int));

        *output << fileNames_[i];

        fileSize = static_cast<int>(boost::filesystem::file_size(directory + fileNames_[i]));
        output->write(reinterpret_cast<char*>(&fileSize), sizeof(unsigned int));
        output->write(reinterpret_cast<char*>(&fileOffset), sizeof(unsigned int));

        fileOffset += fileSize;
        headerLength_ += fileNameLen;
        headerLength_ += 12;
    }

    output->seekg(std::ios::beg);

    // Write header length
    output->write(reinterpret_cast<char*>(&headerLength_), sizeof(unsigned int));
}

void mp::Archiver::writeBody(std::fstream* output,
        const std::string& directory,
        const std::function<void(void* data, size_t size)>& encryption,
        const std::function<void(void* data, size_t size)>& compression)
{
    const unsigned int fileCount = static_cast<unsigned int>(fileNames_.size());

    size_t fileSize;
    std::vector<char> data;
    std::ifstream input;
    output->seekg(headerLength_, std::ios::beg);

    if (encryption) {
        if (compression) {
            for (unsigned int i = fileCount; i-- ; ) {
                input.open(directory + fileNames_[i], std::ios::binary | std::ios::ate);

                fileSize = static_cast<size_t>(input.tellg());
                data.resize(fileSize);

                input.seekg(std::ios::beg);
                input.read(&data.front(), fileSize);
                input.close();

                compression(&data.front(), fileSize);
                encryption(&data.front(), fileSize);
                output->write(&data.front(), fileSize);
            }
        } else
        {
            for (unsigned int i = fileCount; i-- ; ) {
                input.open(directory + fileNames_[i], std::ios::binary | std::ios::ate);

                fileSize = static_cast<size_t>(input.tellg());
                data.resize(fileSize);

                input.seekg(std::ios::beg);
                input.read(&data.front(), fileSize);
                input.close();

                encryption(&data.front(), fileSize);
                output->write(&data.front(), fileSize);
            }
        }
    }
    else {
        if (compression) {
            for (unsigned int i = fileCount; i-- ; ) {
                input.open(directory + fileNames_[i], std::ios::binary | std::ios::ate);

                fileSize = static_cast<size_t>(input.tellg());
                data.resize(fileSize);

                input.seekg(std::ios::beg);
                input.read(&data.front(), fileSize);
                input.close();

                compression(&data.front(), fileSize);
                output->write(&data.front(), data.size());
            }
        } else
        {
            for (unsigned int i = fileCount; i-- ; ) {
                input.open(directory + fileNames_[i], std::ios::binary | std::ios::ate);

                fileSize = static_cast<size_t>(input.tellg());
                data.resize(fileSize);

                input.seekg(std::ios::beg);
                input.read(&data.front(), fileSize);
                input.close();

                output->write(&data.front(), data.size());
            }
        }
    }

    output->close();
}

std::vector<char> mp::Archiver::loadFile(const std::string& inputFile,
    const std::string& targetFile,
    const std::function<void(void* data, size_t size)>& decryption,
    const std::function<void(void* data, size_t size)>& decompression)
{
    std::ifstream input(inputFile);

    if (!input)
        throw std::system_error(errno, std::system_category());

    unsigned int headerLen, fileCount, fileNameLen, fileSize, fileOffset, i=0, offset=8;
    std::string filename;

    // Read header length & file count
    input.read(reinterpret_cast<char*>(&headerLen), sizeof(unsigned int));
    input.read(reinterpret_cast<char*>(&fileCount), sizeof(unsigned int));

    do {
        // Read fileNameLen.
        input.read(reinterpret_cast<char*>(&fileNameLen), sizeof(unsigned int));

        // Read filename
        filename.resize(fileNameLen);
        input.read(&filename[0], fileNameLen);

        if (filename == targetFile) {
            std::vector<char> data;
            // Read the file size.
            input.read(reinterpret_cast<char*>(&fileSize), sizeof(unsigned int));
            // Read the file offset.
            input.read(reinterpret_cast<char*>(&fileOffset), sizeof(unsigned int));

            data.resize(static_cast<std::size_t>(fileSize));
            // Read the whole file.
            input.seekg(headerLen + fileOffset, std::ios::beg);
            input.read(&data.front(), fileSize);

            // Decrypt data.
            if (decryption)
                decryption(&data.front(), fileSize);

            if (decompression)
                decompression(&data.front(), fileSize);

            // The file have been found, no need to keep running the loop.
            return data;
        }

        // Increment offset.
        offset+=fileNameLen;
        offset+=12;

        input.seekg(offset, std::ios::beg);

    } while (++i < fileCount);

    input.close();

    throw std::system_error(ENOENT, std::system_category());

}
