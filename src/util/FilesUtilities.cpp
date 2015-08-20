////////////////////////////////////////////////////////////
//
// MiraiProject
// Copyright (C) 2014-2015 CORTIER Benoît (benoit.cortier@gmail.com), BOULMIER Jérôme (jerome.boulmier@outlook.fr)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
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

#include <cstdio> // fread, fseek, fwrite, ftell
#include <fstream> // std::fstream
#include <vector> // std::vector

#if __unix__
#include <unistd.h>
#include <sys/types.h>
#else
#include <io.h>
#endif

#include <boost/filesystem.hpp> // boost::filesystem::directory_iterator,
                                // boost::filesystem::path

#include "MiraiProject/util/FilesUtilities.hpp"

using namespace std;
using namespace boost::filesystem;

vector<string> mp::filesUtilities::listFiles(path directory, bool recursive)
{
    vector<string> filesPaths;
    vector<string> tempFilesPaths;
    directory_iterator end_itr;

    // Cycle through the directory
    for (directory_iterator itr(directory); itr != end_itr; ++itr)
    {
        // If it's not a directory, add it in filesPaths.
        if (is_regular_file(itr->path()))
        {
            filesPaths.push_back(itr->path().string());
        }
        else if(recursive && is_directory(itr->path()))
        {
            // Else we start another cycle through this directory if we want all files recursively.
            tempFilesPaths = filesUtilities::listFiles(itr->path(), true);
            filesPaths.insert(filesPaths.end(), tempFilesPaths.begin(), tempFilesPaths.end());
        }
    }

    return filesPaths;
}

void mp::filesUtilities::convertToUnixFilePath(std::string* filePath)
{
    std::replace(filePath->begin(), filePath->end(), '\\', '/');
}

void mp::insertData(const std::string& outputPath,
    size_t offset,
    const void* data,
    size_t dataSize)
{
    std::fstream output(outputPath, std::ios::in | std::ios::out | std::ios::binary | std::ios::ate);
    size_t fileSize = output.tellg();

    if (offset > fileSize)
        throw std::out_of_range("Error during insertion of data: offset is bigger than file.");

    shiftData(outputPath, offset, static_cast<int>(dataSize));
    output.seekg(offset, std::ios::beg);
    output.write(static_cast<const char*>(data), dataSize);

    output.close();
}

void mp::shiftData(const std::string& filePath,
    size_t offset,
    int shiftOffset)
{
    // Use of C for truncate and _chsize_s functions.
    FILE *file;
    file = fopen(filePath.c_str(), "rb+");

    // 4 Mo buffer
    const size_t bufferSize = 2097152;
    char* buffer = new char[bufferSize];

    fseek(file, 0, SEEK_END);

    size_t fileSize = ftell(file);

    if (shiftOffset > 0) {
        size_t bytesToMove = fileSize - offset,
            readOffset,
            readEndOffset = fileSize,
            writeOffset,
            bytesThisTime;

        while (bytesToMove) {
            bytesThisTime = std::min(bufferSize, bytesToMove);
            readOffset = readEndOffset - bytesThisTime;
            writeOffset = readOffset + shiftOffset;

            fseek(file, readOffset, SEEK_SET);
            fread(buffer, sizeof(char), bytesThisTime, file);

            fseek(file, writeOffset, SEEK_SET);
            fwrite(buffer, sizeof(char), bytesThisTime, file);

            bytesToMove -= bytesThisTime;
            readEndOffset -= bytesThisTime;

        }
    }
    else {
        size_t bytesToMove = fileSize - offset,
            readOffset = offset,
            writeOffset,
            bytesThisTime;

        while (bytesToMove) {
            bytesThisTime = std::min(bufferSize, bytesToMove);
            writeOffset = readOffset + shiftOffset;

            fseek(file, readOffset, SEEK_SET);
            fread(buffer, sizeof(char), bytesThisTime, file);

            fseek(file, writeOffset, SEEK_SET);
            fwrite(buffer, sizeof(char), bytesThisTime, file);

            bytesToMove -= bytesThisTime;
            readOffset += bytesThisTime;

        }
        #if __unix__
            truncate(filePath.c_str(), fileSize - shiftOffset);
        #else
            int filedes = _fileno(file);
            _chsize_s(filedes, fileSize - shiftOffset);
        #endif
    }

    delete[] buffer;
    fclose(file);
}
