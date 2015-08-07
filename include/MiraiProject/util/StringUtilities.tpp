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

#ifndef STRING_FUNCTIONS_TPP_INCLUDED
#define STRING_FUNCTIONS_TPP_INCLUDED

#include <iostream>
#include <string>
#include <sstream>

#include "MiraiProject/util/StringUtilities.hpp"

using namespace std;

namespace mp
{
    template<typename T>
    string StringUtilities::toString(const T &object)
    {
        ostringstream oss;
        oss << object;
        return oss.str();
    }

    template <typename T>
    T StringUtilities::fromString(const string& str)
    {
        stringstream ss(str);
        T t;
        ss >> t;
        return t;
    }

    template <typename T>
    void StringUtilities::replace(std::basic_string<T>* text, const std::basic_string<T>& toReplace, const std::basic_string<T>& replaceWith)
    {
        size_t pos = 0;
        while ((pos = text->find(toReplace, pos)) != std::string::npos) {
            text->replace(pos, toReplace.length(), replaceWith);
            pos += replaceWith.length();
        }
    }

    template <typename T>
    void mp::StringUtilities::tokenize(const std::basic_string<T>& str,
        std::vector<std::basic_string<T>>* tokens,
        const std::basic_string<T>& delimiters,
        unsigned int limit)
    {
        size_t lastPos = str.find_first_not_of(delimiters, 0),
            pos = str.find_first_of(delimiters, lastPos);

        do {
            tokens->push_back(str.substr(lastPos, pos - lastPos));

            lastPos = str.find_first_not_of(delimiters, pos);
            pos = str.find_first_of(delimiters, lastPos);

        } while ((std::basic_string<T>::npos != pos
            || std::basic_string<T>::npos != lastPos)
            && (!limit || --limit));
    }

}

#endif // STRING_FUNCTIONS_TPP_INCLUDED
