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

namespace mp
{
	class Parser
	{
		public:
			/** \brief For File parsing.
			 * \param inputFile : File to parse.
			 * \param variableName : Name of the variable in file.
			 * \param separator : Characher which separe the variableName and the value.
			 * \param isEncrypted : If inputFile is encrypted.
			 * \param key : Key of file.
			 * 
			 * \return T
			 */ 
			template<typename T> static T fileParser(std::string inputFile, std::string variableName, char separator, bool isEncrypted = false, std::string key = "");
			
			/** \brief Special case for string.
			 * \param inputFile : File to parse.
			 * \param variableName : Name of the variable in file.
			 * \param separator : Characher which separe the variableName and the value.
			 * \param isEncrypted : If inputFile is encrypted.
			 * \param key : Key of file.
			 * 
			 * \return T
			 */ 
			static std::string fileParser(std::string inputFile, std::string variableName, char separator, bool isEncrypted = false, std::string key = "");
			
			/** \brief For File parsing.
			 * \param inputFile : File to parse.
			 * \param variableName : Name of the variable in file.
			 * \param separator : Characher which separe the variableName and the value.
			 * \param isEncrypted : If inputFile is encrypted.
			 * \param key : Key of file.
			 * 
			 * \return a vector<T>
			 */ 
			template<typename T> static std::vector<T> vFileParser(std::string inputFile, std::string variableName, char separator, char separatorValues, bool isEncrypted = false, std::string key = "");
			
			/** \brief For File parsing.
			 * \param inputFile : File to parse.
			 * \param variableName : Name of the variable in file.
			 * \param separator : Characher which separe the variableName and the value.
			 * \param isEncrypted : If inputFile is encrypted.
			 * \param key : Key of file.
			 * 
			 * \return a vector<T>
			 */ 
			static std::vector<std::string> vFileParser(std::string inputFile, std::string variableName, char separator, char separatorValues, bool isEncrypted = false, std::string key = "");
			/** \brief STD put_time which isn't in GCC.
			 * 
			 */
			static std::string put_time(const struct tm* tmb, const std::string &format);
	};
}

#include "MiraiProject/parser/Parser.tpp"

#endif
