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

using namespace std;

int main()
{
    string clearFileName{ "resources/Config.txt" };

    // Read some values from config files.
    bool myBool { };
    vector<int> myIntVector { };
    vector<string> myStringVector { };
    float myFloat { };
    int myInt { };

    myBool = mp::Parser::fileParser<bool>(clearFileName, "someBoolean", '=');
    myIntVector = mp::Parser::vFileParser<int>(clearFileName, "someIntVector", '=', ';');
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

    return 0;
}
