#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

#include "MiraiProject/util/files_functions.hpp"
#include "MiraiProject/util/log.hpp"
#include "MiraiProject/encryption/encrypt_functions.hpp"
#include "MiraiProject/encryption/Encryption.hpp"

#include <boost/filesystem.hpp>

using namespace std;
using namespace mp;
using namespace boost::filesystem;

mp::Encryption::Encryption(string key) : _key{ encrypt_key(key) },
										 _outputFile{ },
										 _offset{ },
										 _filenames{ }
{
	// constructor
}

mp::Encryption::~Encryption()
{
    // destructor
}

bool mp::Encryption::create_file(string outputFile, path directory)
{
    _outputFile = outputFile;
    if(!exists(directory) || !is_directory(directory))
    {
        mp::log("mirai_project.log", mp::level_error, "Path " + directory.string() + " doesn't exist or isn't a directory. (encryption)");
        return false;
    }


    _filenames = list_file(directory);

    if(write_header() && write_data())
        return true;
    else
        return false;

}
bool mp::Encryption::write_header()
{
    bool success = false;
    //Set base offset to 8 bytes (headerlen + filecount).
    long unsigned int offset=8, filecount, fileoffset;
    long unsigned int headerlen;

    vector<long unsigned int> filesize, filenamelen, boffset;

    fstream output(_outputFile, ios::in | ios::out | ios::binary | ios::trunc);
    if(output)
    {
        for(unsigned int i = 0; i<_filenames.size(); i++)
        {
            //Calculate the filename length and push it in filename.
            filenamelen.push_back(_filenames[i].size());
            filesize.push_back(file_size(_filenames[i]));

            // Write the length of the filename on 4 bytes.
            output.seekg(offset,ios::beg);
            output.write(reinterpret_cast<char*>(&filenamelen[i]),4);

            // Write the length of the filename on 4 bytes.
            output << _filenames[i];
            output.write(reinterpret_cast<char*>(&filesize[i]),4);

            // Increment offset (filename length + 4 bytes for write filenamelen
            // 4 bytes for the size and 4 bytes for the offset).
            offset+=filenamelen[i]+4+4+4;
        }

        output.seekg(0,ios::beg);
        encrypt_file(_outputFile);

        //Add the last offset in headerlen and write it.
        headerlen = file_size(_outputFile)+4;
        output.write(reinterpret_cast<char*>(&headerlen),4);

        //Write the number of files which are encrypted.
        filecount = _filenames.size();
        output.write(reinterpret_cast<char*>(&filecount),4);

        //Set base offset to 4, and base fileoffset to headerlen.
        offset=4;
        fileoffset = headerlen;

        for(unsigned int i = 0; i<_filenames.size(); i++)
        {
            offset+=_filenames[i].size()+4+4+4;
            _offset.push_back(fileoffset);

            output.seekg(offset,ios::beg);
            output.write(reinterpret_cast<const char*>(&fileoffset),4);

            fileoffset += filesize[i];
        }
        output.close();
        success = true;
    }
    else
        mp::log("mirai_project.log", mp::level_error, "Unable to open " + _outputFile + " to write the header. (encryption)");

    return success;
}

bool mp::Encryption::write_data()
{
    bool success = false;
    fstream output(_outputFile, ios::in | ios::out | ios::binary);
    if(output)
    {
        for(unsigned int i =0; i<_filenames.size(); i++)
        {
            //Move the cursor to the offset.
            output.seekg(_offset[i],ios::beg);

            //Encrypt the file and write it.
            output << encrypt_file(_filenames[i]);

        }
        output.close();
        success = true;
    }
    else
        mp::log("mirai_project.log", mp::level_error, "Unable to open " + _outputFile + " to write the data. (encryption)");

    return success;
}

string mp::Encryption::encrypt_file(string file)
{
    ifstream input(file, ios::binary);
    if(!input)
		mp::log("mirai_project.log", mp::level_error, "Unable to open " + file + " to crypt the file. (encryption)");

    stringstream buffer;
    string encryptedFile;

    //we read the whole file.
    buffer << input.rdbuf();
    input.close();

    encryptedFile = static_cast<string>(buffer.str());

    //Encrypt the file
    encryptedFile = encrypt_data(_key, encryptedFile);

    return encryptedFile;
}

string mp::Encryption::load_file(string inputFile, string targetFile)
{

    int headerlen, filecount, filenamelen, filesize, fileoffset, i=0, offset=8;

    ifstream input(inputFile, ios::in | ios::binary);
    if(!input)
		mp::log("mirai_project.log", mp::level_error, "Unable to open " + inputFile + " to parse the header. (encryption)");

    string filename;

    //Read headerlen & filecount
    input.read(reinterpret_cast<char*>(&headerlen), 4);
    input.read(reinterpret_cast<char*>(&filecount), 4);

    while(i<filecount)
    {
        //read the filenamelen.
        input.seekg(offset,ios::beg);
        input.read(reinterpret_cast<char*>(&filenamelen), 4);

        //Possible memory leak.
        char * buffer = new char[filenamelen];

        //read filenamelen
        input.read(buffer, filenamelen);
        filename = buffer;

        //increment the offset with filenamelen.
        offset+=filenamelen+4+4+4;

        if(filename == targetFile)
        {
            //read the filesize into the input file.
            input.read(reinterpret_cast<char*>(&filesize), 4);
            //read the fileoffset into the input file.
            input.read(reinterpret_cast<char*>(&fileoffset), 4);

            //Move the cursor on the first bit of the file and read it with filesize.
            std::string file(filesize, ' ');
            input.seekg(fileoffset, ios::beg);
            input.read(&file[0], filesize);

            //convert in order to use crypt_data function.
            file = encrypt_data(_key, file);

            //The file have been found, no need to keep running the loop.
            return file;
        }
        i++;
    }

    input.close();


    return "";
}
