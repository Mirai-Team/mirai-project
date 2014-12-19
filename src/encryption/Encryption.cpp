#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

#include "util/files_functions.hpp"
#include "encryption/crypt_function.hpp"
#include "encryption/Encryption.hpp"

using namespace std;
using namespace mp;

mp::Encryption::Encryption(string key, string data)
{
    _key= key;
    _data = data;

    //Encrypt the key.
    _key = crypt_key(_key);

}

mp::Encryption::~Encryption()
{
    //dtor
}

void mp::Encryption::create_file(string outputFile, vector<string>filenames)
{
    _outputFile = outputFile;
    _filenames = filenames;
    write_header();
    write_data();

}
void mp::Encryption::write_header()
{
    //Set base offset to 8 bytes (headerlen + filecount).
    long int offset=8, filecount, fileoffset;
    int headerlen;

    vector<long int> filesize, filenamelen, boffset;

    fstream output(_outputFile, ios::in | ios::out | ios::binary | ios::trunc);

    for(unsigned int i = 0; i<_filenames.size(); i++)
    {
        //Calculate the filename length and push it in filename.
        filenamelen.push_back(_filenames[i].size());
        filesize.push_back(get_file_size(_filenames[i]));

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
    crypt_file(_outputFile);

    //Add the last offset in headerlen and write it.
    headerlen = get_file_size(_outputFile)+4;
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

}

void mp::Encryption::write_data()
{
    fstream output(_outputFile, ios::in | ios::out | ios::binary);

    for(unsigned int i =0; i<_filenames.size(); i++)
    {
        //Move the cursor to the offset.
        output.seekg(_offset[i],ios::beg);

        //Encrypt the file and write it.
        output << crypt_file(_filenames[i]);

    }
    output.close();
}

string mp::Encryption::crypt_file(string file)
{
    ifstream input(file, ios::binary);
    stringstream buffer;
    string cryptedFile;

    //we read the whole file.
    buffer << input.rdbuf();
    input.close();

    cryptedFile = static_cast<string>(buffer.str());

    //Encrypt the file
    cryptedFile = crypt_data(_key, cryptedFile);

    return cryptedFile;
}

string mp::Encryption::parse_header(string inputFile, string targetFile)
{
	_inputFile = inputFile;

    bool found = false;

    int headerlen, filecount, filenamelen, filesize, fileoffset, i=0, offset=8;

    ifstream input(_inputFile, ios::in | ios::binary);

    string filename, file;

    //Read headerlen & filecount
    input.read(reinterpret_cast<char*>(&headerlen), 4);
    input.read(reinterpret_cast<char*>(&filecount), 4);

    while(i<filecount && found==false)
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

            char * buffer2 = new char[filesize];

            //Move the cursor on the first bit of the file and read it with filesize.
            input.seekg(fileoffset, ios::beg);
            input.read(buffer2, filesize);

            //convert in order to use crypt_data function.
            file = buffer2;
            file = crypt_data(_key, file);

            //The file have been found, no need to keep running the loop.
            found = true;
        }
    }

    input.close();

    return file;

}
