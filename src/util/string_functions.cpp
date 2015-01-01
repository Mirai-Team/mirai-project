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

#include <string>
#include <algorithm> // remove(), erase()
#include <sstream> // for locale

#include "MiraiProject/util/string_functions.hpp"

using namespace std;

void mp::stripLetter(string &str, const char &letter)
{
    str.erase(remove(str.begin(), str.end(), letter), str.end());
}

string mp::upper(string text)
{
    locale loc;

    for (unsigned int i{ 0 } ; i < text.length() ; i++)
    {
        text[i] = toupper(text[i], loc);
    }

    return text;
}

vector<string> mp::split(const string &text, const char &separator, unsigned int limit)
{
    istringstream iss{ text };
    string word;
    vector<string> words;

    unsigned int i{ 0 };
    while (getline(iss, word, separator) and limit != 0 and i < limit)
    {
        i++;
        words.push_back(word);
    }

    return words;
}

string mp::replace(string &text, string toReplace, string replaceWith)
{
    return(text.replace(text.find(toReplace), toReplace.length(), replaceWith));
}
