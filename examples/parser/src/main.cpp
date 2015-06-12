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
#include <string>
#include <sstream>
#include <vector>

#include <MiraiProject/parser/Parser.hpp>
#include <MiraiProject/encryption/Encryption.hpp>

using namespace std;

int main()
{
    string encryptionKey{ "someKeyForEncryption" };

    mp::Encryption encryptMotor(encryptionKey);

    string clearFileName{ "resources/clearConfig.txt" };
    string encryptedFileName{ "resources/encryptedConfig.txt" };
    string decryptedFileName{ "resources/decryptedConfig.txt" };

    string encryptedData{ };
    string decryptedData{ };

    ofstream file;

    cout << "Trying to encrypt " << clearFileName << "." << endl;

    // Encrypt config file.
    encryptedData = encryptMotor.encryptFile(clearFileName);

    if (encryptedData != "")
    {
        file.open(encryptedFileName, ios::trunc);
        file << encryptedData;
        file.close();

        cout << "Encryption successful." << endl;

        cout << "Trying to decrypt " << encryptedFileName << "." << endl;

        // Decrypt encrypted config file.
        decryptedData = encryptMotor.encryptFile(encryptedFileName);
        file.open(decryptedFileName, ios::trunc);
        file << decryptedData;
        file.close();

        cout << "Decryption successful." << endl;

        // Read some values from config files.
        bool myBool { };
        vector<int> myIntVector { };
        vector<string> myStringVector { };
        float myFloat { };
        int myInt { };

        // From the encrypted config file.
        myBool = mp::Parser::fileParser<bool>(encryptedFileName, "someBoolean", '=', true, encryptionKey);
        myIntVector = mp::Parser::vFileParser<int>(encryptedFileName, "someIntVector", '=', ';', true, encryptionKey);

        // From the clear config file.
        myStringVector = mp::Parser::vFileParser<string>(clearFileName, "someStringVector", '=', ';');
        myFloat = mp::Parser::fileParser<float>(clearFileName, "someFloatValue", '=');
        myInt = mp::Parser::fileParser<int>(clearFileName, "someIntValue", '=');

        // Let's print what we got.
        cout << "someBoolean = " << myBool << endl;

        cout << "someIntVector =";
        for (auto value : myIntVector)
            cout << " " << value;
        cout << endl;

        cout << "someStringVector =";
        for (auto value : myStringVector)
            cout << " " << value;
        cout << endl;

        cout << "someFloatValue = " << myFloat << endl;
        cout << "someIntValue = " << myInt << endl;
    }
    else
        cout << clearFileName << " is not found or empty." << endl;

    return 0;
}
