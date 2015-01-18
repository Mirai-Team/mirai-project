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

#ifndef ENCRYPTION_HPP_INCLUDED
#define ENCRYPTION_HPP_INCLUDED

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <boost/filesystem.hpp>

std::vector<std::string> listFiles(boost::filesystem::path directory, bool recursive);
std::vector<std::string> split(const std::string &text);

std::string encryptKey(std::string key);
std::string encryptData(std::string key, std::string data);

std::string encryptFile(std::string file);

void encryptFiles(std::string key, boost::filesystem::path directory, std::string outputFile);
void decryptFiles(std::string key, std::string inputFile);


bool writeHeader(std::vector<std::string> fileNames);
bool writeData(std::vector<std::string> fileNames);

#endif