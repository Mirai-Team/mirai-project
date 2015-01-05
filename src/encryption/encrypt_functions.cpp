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

#include <iostream>
#include <fstream>

#include "MiraiProject/encryption/Encryption.hpp"

using namespace std;

string mp::Encryption::encryptKey(string key)
{
    //Apply a NOT on each bit from each character of key string.
    for(unsigned int i=0; i<key.length(); i++)
        key[i] = static_cast<char>( ~key[i] );

    return key;
}

string mp::Encryption::encryptData(string key, string data)
{
    //Apply a XOR between the key MOD length() and data.
    for(unsigned int i=0; i<data.length(); i++)
        data[i] = static_cast<char>( data[i] ^ key[i%key.length()] );
    return data;
}
