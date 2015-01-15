////////////////////////////////////////////////////////////
//
// MiraiProject
// Copyright (C) 2014-2015 CORTIER Benoît (benoit.cortier@gmail.com), BOULMIER Jérôme (jerome.boulmier@outlook.com)
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

#include "encryption.hpp"

using namespace std;
using namespace boost::filesystem;

std::string outputFile_;
std::string key_;
std::vector<long int>offset_;

bool writeHeader(vector<string> fileNames)
{
    bool hasSuccess = false;
    //Set base offset to 8 bytes (headerLen + fileCount).
    long unsigned int offset=8, fileCount, fileOffset;
    long unsigned int headerLen;

    vector<long unsigned int> fileSize, fileNameLen;

    fstream output(outputFile_, ios::in | ios::out | ios::binary | ios::trunc);
    if(output)
    {
        for(unsigned int i = 0; i<fileNames.size(); i++)
        {
            //Calculate the filename length and push it in filename.
            fileNameLen.push_back(fileNames[i].size());
            fileSize.push_back(file_size(fileNames[i]));

            // Write the length of the filename on 4 bytes.
            output.seekg(offset,ios::beg);
            output.write(reinterpret_cast<char*>(&fileNameLen[i]),4);

            // Write the length of the filename on 4 bytes.
            output << fileNames[i];
            output.write(reinterpret_cast<char*>(&fileSize[i]),4);

            // Increment offset (filename length + 4 bytes for write filenamelen
            // 4 bytes for the size and 4 bytes for the fileoffset).
            offset+=fileNameLen[i]+4+4+4;
        }

        output.seekg(0,ios::beg);
        encryptFile(outputFile_);

        //Add the last offset in headerlen and write it.
        headerLen = file_size(outputFile_)+4;
        output.write(reinterpret_cast<char*>(&headerLen),4);

        //Write the number of files which are encrypted.
        fileCount = fileNames.size();
        output.write(reinterpret_cast<char*>(&fileCount),4);

        //Set base offset to 4, and base fileoffset to headerlen.
        offset=4;
        fileOffset = headerLen;

        for(unsigned int i = 0; i<fileNames.size(); i++)
        {
            offset+=fileNames[i].size()+4+4+4;
            offset_.push_back(fileOffset);

            output.seekg(offset,ios::beg);
            output.write(reinterpret_cast<const char*>(&fileOffset),4);

            fileOffset += fileSize[i];
        }
        output.close();
        hasSuccess = true;
    }
    else
        cout << "Unable to open " << outputFile_ << " to write the header. (encryption)";

    return hasSuccess;
}

string encryptFile(string file)
{
    ifstream input(file, ios::binary);
    if(!input)
		cout << "Unable to open " << file << " to crypt the file. (encryption)";

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

string encryptKey(string key)
{
    //Apply a NOT on each bit from each character of key string.
    for(unsigned int i=0; i<key.length(); i++)
        key[i] = static_cast<char>( ~key[i] );

    return key;
}

string encryptData(string key, string data)
{
    //Apply a XOR between the key MOD length() and data.
    for(unsigned int i=0; i<data.length(); i++)
        data[i] = static_cast<char>( data[i] ^ key[i%key.length()] );
    return data;
}

bool writeData(vector<string> fileNames)
{
    bool hasSuccess = false;
    fstream output(outputFile_, ios::in | ios::out | ios::binary);
    if(output)
    {
        for(unsigned int i =0; i<fileNames.size(); i++)
        {
            //Move the cursor to the offset.
            output.seekg(offset_[i],ios::beg);

            //Encrypt the file and write it.
            output << encryptFile(fileNames[i]);

        }
        output.close();
        hasSuccess = true;
    }
    else
        cout << "Unable to open " << outputFile_ << " to write the data. (encryption)";

    return hasSuccess;
}

void decryptFiles(std::string key, std::string inputFile)
{
	key_ = key;
    int headerLen, fileCount, fileNameLen, fileSize, fileOffset, i=0, offset=8;

    ifstream input(inputFile, ios::in | ios::binary);
    if(!input)
		cout << "Unable to open " << inputFile << " to parse the header. (encryption)";

    //string filename;

    //Read headerlen & filecount
    input.read(reinterpret_cast<char*>(&headerLen), 4);
    input.read(reinterpret_cast<char*>(&fileCount), 4);

    while(i<fileCount)
    {
        //read the filenamelen.
        input.seekg(offset,ios::beg);
        input.read(reinterpret_cast<char*>(&fileNameLen), 4);

        //read filename
        std::string filename(fileNameLen, ' ');
        input.read(&filename[0], fileNameLen);
        
        //increment the offset with filenamelen.
        offset+=fileNameLen+4+4+4;

		//read the filesize into the input file.
		input.read(reinterpret_cast<char*>(&fileSize), 4);
		//read the fileoffset into the input file.
		input.read(reinterpret_cast<char*>(&fileOffset), 4);

		//Move the cursor on the first bit of the file and read it with filesize.
		std::string file(fileSize, ' ');
		input.seekg(fileOffset, ios::beg);
		input.read(&file[0], fileSize);

		//decrypt file
		file = encryptData(key_, file);
		
		//extract and create directory
		vector<string> temp;
		temp = split(filename);
		string directory;
		for(unsigned int j = 0; j < temp.size() - 1; j++)
		{
			directory += temp[j] + "/";
			path dir(directory);
			if(!is_directory(dir))
				create_directory(dir);
		}
		
		//write file
		ofstream output(filename, ios::binary);
		output << file;
		output.close();

        i++;
    }

    input.close();

}

void encryptFiles(string key, path directory, string outputFile)
{
	vector<string>fileNames;
	key_ = key;
	outputFile_ = outputFile;
	if(!exists(directory) || !is_directory(directory))
    {
        cout << "Path " << directory.string() << " doesn't exist or isn't a directory. (encryption)";
    }


    fileNames = listFiles(directory, true);
	
	//In order to keep cross-plateform
	string windowsSeparator { "\\" };
	string unixSeparator { "/" };

	std::replace(fileNames.begin(), fileNames.end(), windowsSeparator, unixSeparator);
		
    writeHeader(fileNames);
    writeData(fileNames);
}

vector<string> listFiles(path directory, bool recursive)
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
            tempFilesPaths = listFiles(itr->path(), true);
            filesPaths.insert(filesPaths.end(), tempFilesPaths.begin(), tempFilesPaths.end());
        }

    }
	
    return filesPaths;
}

vector<string> split(const string &text)
{
    istringstream iss{ text };
    vector<string> words;

   for (std::string each; std::getline(iss, each, '/'); words.push_back(each));

    return words;
}
