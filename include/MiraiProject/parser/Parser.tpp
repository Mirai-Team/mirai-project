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

#include <fstream>
#include <vector>
#include <string>

#include "MiraiProject/parser/Parser.hpp"
#include "MiraiProject/util/StringUtilities.hpp"
#include "MiraiProject/util/Logger.hpp"

using namespace std;

namespace mp
{
	template<typename T> T mp::Parser::FileParser(std::string inputFile, std::string variableName, char separator)
	{
		ifstream file;
		string line;
		vector<string> words;
		T temp;
		mp::Logger log("mirai_project.log");
		
		file.open(inputFile, ios::in);
		
		if(file)
		{
			while(getline(file,line))
			{
				words = mp::StringUtilities::split(line, separator);
				if(words[0] == variableName)
					temp = mp::StringUtilities::fromString<T>(words[1]);
			}
		}
		else
		{
			log(priorityWarning) << "The file doesn't exist";
		}
		
		return temp;
		
	}


}
