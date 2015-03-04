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

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

#include "MiraiProject/util/FilesUtilities.hpp"
#include "MiraiProject/util/Logger.hpp"
#include "MiraiProject/util/StringUtilities.hpp"
#include "MiraiProject/encryption/Encryption.hpp"

#include <boost/filesystem.hpp>

using namespace std;
using namespace boost::filesystem;

mp::Encryption::Encryption(string key) : key_{ encryptKey(key) },
                                         outputFile_{ },
                                         offset_{ },
                                         fileNames_{ },
                                         log_ { "mirai_project.log" }
{
    // constructor
}

mp::Encryption::~Encryption()
{
    // destructor
}

bool mp::Encryption::createFile(string outputFile, path directory)
{
    outputFile_ = outputFile;
    if(!exists(directory) || !is_directory(directory))
    {
        log_(mp::Logger::priorityError) << "Path " << directory.string() << " doesn't exist or isn't a directory. (encryption)";
        return false;
    }

    fileNames_ = filesUtilities::listFiles(directory, true);

    // In order to keep cross-plateform, we replace windowsSeparator by unixSeparator
    char windowsSeparator = '\\' ;
    char unixSeparator = '/' ;

    for(unsigned int i = 0; i < fileNames_.size(); i++)
    {
        for(unsigned int j = 0; j <fileNames_[i].size(); j++)
        {
            if(fileNames_[i][j] == windowsSeparator)
                fileNames_[i][j] = unixSeparator;
        }
    }
    
    if(writeHeader() && writeData())
        return true;
    else
        return false;

}
bool mp::Encryption::writeHeader()
{
    bool hasSuccess = false;

    // Set base offset to 8 bytes (headerLen + fileCount).
    long unsigned int offset=8;
    long unsigned int headerLen, fileCount, fileOffset;

    vector<long unsigned int> fileSize, fileNameLen;

    fstream output(outputFile_, ios::in | ios::out | ios::binary | ios::trunc);

    if(output)
    {
        for(unsigned int i = 0; i<fileNames_.size(); i++)
        {
            // Calculate the filename length and push it in filename.
            fileNameLen.push_back(fileNames_[i].size());
            fileSize.push_back(file_size(fileNames_[i]));

            // Write the length of the filename on 4 bytes.
            output.seekg(offset,ios::beg);
            output.write(reinterpret_cast<char*>(&fileNameLen[i]),4);

            // Write the length of the filename on 4 bytes.
            output << fileNames_[i];
            output.write(reinterpret_cast<char*>(&fileSize[i]),4);

            // Increment offset (filename length + 4 bytes for write filenamelen
            // 4 bytes for the size and 4 bytes for the fileoffset).
            offset+=fileNameLen[i]+4+4+4;
        }

        output.seekg(0,ios::beg);
        encryptFile(outputFile_);

        // Add the last offset in headerlen and write it.
        headerLen = file_size(outputFile_)+4;
        output.write(reinterpret_cast<char*>(&headerLen),4);

        // Write the number of files which are encrypted.
        fileCount = fileNames_.size();
        output.write(reinterpret_cast<char*>(&fileCount),4);

        // Set base offset to 4, and base fileoffset to headerlen.
        offset=4;
        fileOffset = headerLen;

        for(unsigned int i = 0; i<fileNames_.size(); i++)
        {
            // Calculate offset
            offset+=fileNames_[i].size()+4+4+4;

            // Push fileOffset in offset_ for writeData() method.
            offset_.push_back(fileOffset);

            // Write offset in fileOffset.
            output.seekg(offset,ios::beg);
            output.write(reinterpret_cast<const char*>(&fileOffset),4);

            fileOffset += fileSize[i];
        }

        output.close();

        hasSuccess = true;
    }
    else
        log_(mp::Logger::priorityError) << "Unable to open " << outputFile_ << " to write the header. (encryption)";

    return hasSuccess;
}

bool mp::Encryption::writeData()
{
    bool hasSuccess = false;

    fstream output(outputFile_, ios::in | ios::out | ios::binary);

    if(output)
    {
        for(unsigned int i =0; i<fileNames_.size(); i++)
        {
            //Move the cursor to the offset.
            output.seekg(offset_[i],ios::beg);

            //Encrypt the file and write it.
            output << encryptFile(fileNames_[i]);

        }

        output.close();

        hasSuccess = true;
    }
    else
        log_(mp::Logger::priorityError) << "Unable to open " << outputFile_ << " to write the data. (encryption)";

    return hasSuccess;
}

string mp::Encryption::encryptFile(string file)
{
    ifstream input(file, ios::binary);
    if(!input)
        log_(mp::Logger::priorityError) << "Unable to open " << file << " to crypt the file. (encryption)";

    stringstream buffer;
    string encryptedFile;

    //we read the whole file.
    buffer << input.rdbuf();
    input.close();

    encryptedFile = static_cast<string>(buffer.str());

    //Encrypt the file
    encryptedFile = encryptData(key_, encryptedFile);

    return encryptedFile;
}

string mp::Encryption::loadFile(string inputFile, string targetFile)
{

    int headerLen, fileCount, fileNameLen, fileSize, fileOffset, i=0, offset=8;

    ifstream input(inputFile, ios::in | ios::binary);
    if(!input)
        log_(mp::Logger::priorityError) << "Unable to open " << inputFile << " to parse the header. (encryption)";


    // Read headerlen & filecount
    input.read(reinterpret_cast<char*>(&headerLen), 4);
    input.read(reinterpret_cast<char*>(&fileCount), 4);

    while(i<fileCount)
    {
        // Read the filenamelen.
        input.seekg(offset,ios::beg);
        input.read(reinterpret_cast<char*>(&fileNameLen), 4);

        // Read filename
        string filename(fileNameLen, ' ');
        input.read(&filename[0], fileNameLen);

        // Increment the offset with filenamelen.
        offset+=fileNameLen+4+4+4;

        if(filename == targetFile)
        {
            // Read the filesize into the input file.
            input.read(reinterpret_cast<char*>(&fileSize), 4);
            // Read the fileoffset into the input file.
            input.read(reinterpret_cast<char*>(&fileOffset), 4);

            // Move the cursor on the first bit of the file and read it with filesize.
            std::string file(fileSize, ' ');
            input.seekg(fileOffset, ios::beg);
            input.read(&file[0], fileSize);

            // Convert in order to use crypt_data function.
            file = encryptData(key_, file);

            // The file have been found, no need to keep running the loop.
            return file;
        }
        i++;
    }

    input.close();

    return "";
}

string mp::Encryption::encryptKey(string key)
{
    // Apply a NOT on each bit from each character of key string.
    for(unsigned int i=0; i<key.length(); i++)
        key[i] = static_cast<char>( ~key[i] );

    return key;
}

string mp::Encryption::encryptData(string key, string data)
{
    // Apply a XOR between the key MOD length() and data.
    for(unsigned int i=0; i<data.length(); i++)
        data[i] = static_cast<char>( data[i] ^ key[i%key.length()] );
    return data;
}