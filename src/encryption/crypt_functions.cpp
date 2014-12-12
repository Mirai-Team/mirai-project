#include <iostream>
#include <fstream>

#include "encryption/crypt_function.hpp"

using namespace std;

string mp::CryptKey(string key)
{
    //Apply a NOT on each bit from each character of key string.
    for(unsigned int i=0; i<key.length(); i++)
        key[i] = static_cast<char>( ~key[i] );

    return key;
}

string mp::CryptData(string key, string data)
{
    //Apply a XOR between the key MOD length() and data.
    for(unsigned int i=0; i<data.length(); i++)
        data[i] = static_cast<char>( data[i] ^ key[i%key.length()] );
    return data;
}
