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

#include <boost/filesystem.hpp>
#include <MiraiProject/encryption/Encryption.hpp>
#include <MiraiProject/util/Logger.hpp>

int main()
{
    std::string outputFile { "resources/data.bin" };
    std::ofstream data;

    // We create a directory and write data in a file
    boost::filesystem::create_directory("resources/");
    boost::filesystem::create_directory("resources/data/");
    data.open("resources/data/log.txt",std::ios::binary);
    data << "Mirai Encryption example" << std::endl;
    data.close();

    // Constructor with key parameter.
    mp::Encryption fileEncrypt("mirai");
    boost::filesystem::path directoryToEncrypt("resources/data/");

    // Creation of a file with data/ directory.
    fileEncrypt.createFile(outputFile, directoryToEncrypt);
    // Now our data are encrypted in data.bin.

    // We are looking for the picture through the file.
    std::string output = fileEncrypt.loadFile(outputFile, "resources/data/log.txt");

    // We open a file and write data in it.
    std::ofstream file;
    file.open("output.txt",std::ios::binary);

    file << output;

    file.close();
}