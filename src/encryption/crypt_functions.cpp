#include <iostream>
#include <fstream>

#include "encryption/crypt_function.hpp"
#include "util/file_functions.hpp"

using namespace std;

string mp::crypt_key(string key)
{
    //Apply a NOT on each bit from each character of key string.
    for(unsigned int i=0; i<key.length(); i++)
        key[i] = static_cast<char>( ~key[i] );

    return key;
}

string mp::crypt_data(string key, string data)
{
    //Apply a XOR between the key MOD length() and data.
    for(unsigned int i=0; i<data.length(); i++)
        data[i] = static_cast<char>( data[i] ^ key[i%key.length()] );
    return data;
}

void mp::write_header(string output_file, vector<string> filenames, string key)
{
    //Set base offset to 8 bytes (headerlen + filecount).
    long int offset=8, filecount, fileoffset;
    int headerlen;

    vector<long int> filesize, filenamelen, boffset;

    fstream output(output_file, ios::in | ios::out | ios::binary | ios::trunc);

    //Encrypt the key.
    key = crypt_key(key);

    for(unsigned int i = 0; i<filenames.size(); i++)
    {
        //Calculate the filename length and push it in filename.
        filenamelen.push_back(filenames[i].size());
        filesize.push_back(get_file_size(filenames[i]));

        // Write the length of the filename on 4 bytes.
        output.seekg(offset,ios::beg);
        output.write(reinterpret_cast<char*>(&filenamelen[i]),4);

        // Write the length of the filename on 4 bytes.
        output << filenames[i];
        output.write(reinterpret_cast<char*>(&filesize[i]),4);

        // Increment offset (filename length + 4 bytes for write filenamelen
        // 4 bytes for the size and 4 bytes for the offset).
        offset+=filenamelen[i]+4+4+4;
    }

    output.seekg(0,ios::beg);

    //Add the last offset in headerlen and write it.
    headerlen = get_file_size(output_file)+4;
    output.write(reinterpret_cast<char*>(&headerlen),4);

    //Write the number of files which are encrypted.
    filecount = filenames.size();
    output.write(reinterpret_cast<char*>(&filecount),4);

    //Set base offset to 4, and base fileoffset to headerlen.
    offset=4;
	fileoffset = headerlen;

    for(unsigned int i = 0; i<filenames.size(); i++)
    {
        offset+=filenames[i].size()+4+4+4;
        boffset.push_back(fileoffset);

        //Write fileoffset
        output.seekg(offset,ios::beg);
        output.write(reinterpret_cast<const char*>(&fileoffset),4);

        fileoffset += filesize[i];
    }
    output.close();
    write_data(output_file, filenames,boffset, key);

}

void mp::write_data(string output_file, vector<string> filenames, vector<long int>offset, string key)
{
    fstream output(output_file, ios::in | ios::out | ios::binary);

    for(unsigned int i =0; i<filenames.size(); i++)
    {
        ifstream input(filenames[i], ios::binary);
        stringstream buffer;
        string write_buffer;

        //we read the whole file.
        buffer << input.rdbuf();
        write_buffer = static_cast<string>(buffer.str());

        //Move the cursor to the offset.
        output.seekg(offset[i],ios::beg);

        //Encrypt the file and write it.
        write_buffer = crypt_data(key,write_buffer);
        output << write_buffer;

        input.close();
    }
    output.close();
}
void mp::parse_header(string inputfile, string targetFile,string key)
{
    bool found = false;

    int headerlen, filecount, filenamelen, filesize, fileoffset, i=0, offset=8;

    ifstream input(inputfile, ios::in | ios::binary);

    string filename, file;

    key = crypt_key(key);

    input.seekg(0,ios::beg);
    input.read(reinterpret_cast<char*>(&headerlen), 4);
    input.read(reinterpret_cast<char*>(&filecount), 4);

    while(i<filecount and found==false)
    {
        //read the filenamelen.
        input.seekg(offset,ios::beg);
        input.read(reinterpret_cast<char*>(&filenamelen), 4);

        //Possible memory leak.
        char * buffer = new char[filenamelen];

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
            file = crypt_data(key,file);

            //The file have been found, no need to keep running the loop.
            found = true;
        }
    }

    input.close();

}
