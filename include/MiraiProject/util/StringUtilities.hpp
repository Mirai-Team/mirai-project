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

#ifndef STRINGUTILITIES_HPP_INCLUDED
#define STRINGUTILITIES_HPP_INCLUDED

#include <string>
#include <vector>

/** @file string_functions.hpp
 * \brief This file define various functions to manipulate std::string.
 */

namespace mp
{
    /** \class StringUtilities
     * \brief A static class with various functions to manipulate std::string.
     */

    class StringUtilities
    {
        public:
            /** \brief Remove the given letter from the given string.
             *
             * The string is updated by reference.
             *
             * \param str : the string to modify by reference.
             * \param letter : the letter to remove.
             */
            static void stripLetter(std::string &str, const char &letter);

            /** \brief Get a uppercase version from a string.
             *
             * \param text : the string to convert.
             *
             * \return the given string but with each character in uppercase.
             */
            static std::string upper(std::string text);

            /** \brief Split the given string using the given separator (a single letter).
             *
             * \param text : the text to explode.
             * \param separator : the character to use as separator.
             * \param limit : specifies the number of separator until the function stop splitting. If limit = 0, there is no limit
             *
             * \return all part of the given string in a vector<string>.
             */
            static std::vector<std::string> split(const std::string &text, const char &separator, unsigned int limit=0);

            /** \brief Replace all chosen occurrences by a given substring in the given text.
             *
             * \param text : the text where replace operation should be operated.
             * \param toReplace : occurrence to replace.
             * \param replaceWith : string which will replace the occurrences.
             *
             */
            template<typename T>
            static void replace(std::basic_string<T>* text, const std::basic_string<T>& toReplace, const std::basic_string<T>& replaceWith);

            /** \brief Convert the given object into string if possible by using an ostringstream object.
             *
             * \param object : the object to convert.
             *
             * \return the given object converted into string.
             */
            template<typename T> static std::string toString(const T &object);

            /** \brief Convert string content to T type.
             *
             * \param str : the string.
             *
             * \return the converted value into the type T.
             */
            template <typename T> static T fromString(const std::string& str);
    };
}

#include "MiraiProject/util/StringUtilities.tpp"

#endif // STRINGUTILITIES_HPP_INCLUDED
