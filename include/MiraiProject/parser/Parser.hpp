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

#ifndef PARSER_HPP_INCLUDED
#define PARSER_HPP_INCLUDED

#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <vector>

/** @file Parser.hpp
 * \brief This file define Parser class.
 */

namespace mp
{
    /** \class Parser
     * \brief A class for file parsing.
     */

    class Parser
    {
        public:
            /** \brief For File parsing.
             *
             * \param inputFile : File to parse.
             * \param variableName : Name of the variable in file.
             * \param separator : Character which separe the variableName and the value.
             * \param isEncrypted : If inputFile is encrypted.
             * \param key : Key of file.
             * 
             * \return T
             */ 
            template<typename T> static T fileParser(std::string inputFile, std::string variableName, char separator, bool isEncrypted = false, std::string key = "");

            /** \brief Special case for string.
             *
             * \param inputFile : File to parse.
             * \param variableName : Name of the variable in file.
             * \param separator : Character which separe the variableName and the value.
             * \param isEncrypted : If inputFile is encrypted.
             * \param key : Key of file.
             * 
             * \return T
             */ 
            static std::string fileParser(std::string inputFile, std::string variableName, char separator, bool isEncrypted = false, std::string key = "");

            /** \brief For File parsing.
             *
             * \param inputFile : File to parse.
             * \param variableName : Name of the variable in file.
             * \param separator : Character which separe the variableName and the value.
             * \param isEncrypted : If inputFile is encrypted.
             * \param key : Key of file.
             * 
             * \return a vector<T>
             */ 
            template<typename T> static std::vector<T> vFileParser(std::string inputFile, std::string variableName, char separator, char separatorValues, bool isEncrypted = false, std::string key = "");

            /** \brief For File parsing.
             *
             * \param inputFile : File to parse.
             * \param variableName : Name of the variable in file.
             * \param separator : Character which separe the variableName and the value.
             * \param isEncrypted : If inputFile is encrypted.
             * \param key : Key of file.
             * 
             * \return a vector<T>
             */ 
            static std::vector<std::string> vFileParser(std::string inputFile, std::string variableName, char separator, char separatorValues, bool isEncrypted = false, std::string key = "");

            /** \brief std-like put_time function which isn't in GCC.
             *
             * Format codes for format string :
             *   - %%a : abbreviated weekday name (ex : Sun).
             *   - %%A : full weekday name (ex : Sunday).
             *   - %%b : abbreviated month name (ex : Jan).
             *   - %%B : full month name (ex : January).
             *   - %%c : date and time representation (ex : Thu Aug 23 14:55:02 2001).
             *   - %%C : year divided by 100 and truncated to integer (00-99) (ex : 10).
             *   - %%d : day of the month, zero-padded (01-31) (ex : 07).
             *   - %%D : short MM/DD/YY date, equivalent to %%m/%%d/%%y (ex : 03/28/14).
             *   - %%e : day of the month, space-padded ( 1-31) (ex : 7).
             *   - %%F : short YYYY-MM-DD date, equivalent to %Y-%m-%d (ex : 2014-03-28).
             *   - %%g : week-based year, last two digits (00-99) (ex : 15). ==> To implement.
             *   - %%G : week-based year (ex : 2015).
             *   - %%h : abbreviated month name (same as %%b) (ex : Sun).
             *   - %%H : hour in 24h format (00-23) (ex : 22). ==> To implement.
             *   - %%I : hour in 12h format (01-12) (ex : 06). ==> To implement.
             *   - %%m : month as a decimal number (01-12) (ex : 03).
             *   - %%M : minute (00-59) (ex : 11).
             *   - %%n : new-line character ('\\n').
             *   - %%R : 24-hour HH:MM time, equivalent to %H:%M (ex : 14:55).
             *   - %%S : second (00-61) (ex : 52).
             *   - %%t : horizontal-tab character ('\\t').
             *   - %%T : ISO 8601 time format (HH:MM:SS), equivalent to %H:%M:%S (ex : 13:14:52).
             *   - %%w : weekday as a decimal number with Sunday as 0 (0-6).
             *   - %%y : year, last two digits (00-99) (ex : 15).
             *   - %%Y : Year (ex : 2015).
             *
             * \param tmb : pointer to the calendar time structure as obtained from localtime() or gmtime().
             * \param format : the format string to format the output.
             *
             * \return the formatted string.
             */
            static std::string put_time(const struct tm* tmb, const std::string &format);
    };
}

#include "MiraiProject/parser/Parser.tpp"

#endif