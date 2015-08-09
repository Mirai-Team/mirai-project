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

#include <fstream>
#include <iostream>
#include <vector>

#include <boost/filesystem.hpp>

#include <MiraiProject/util/Logger.hpp>
#include <MiraiProject/util/Archiver.hpp>

int main()
{
    std::string outputFile { "resources/data.bin" };
    std::ofstream file;

    // We create a directory and write data in a file
    boost::filesystem::create_directory("resources/");
    boost::filesystem::create_directory("resources/data/");
    file.open("resources/data/log.txt",std::ios::binary);
    file << "Mirai archiver example" << std::endl;
    file.close();

    // Constructor.
    mp::Archiver archiver;
    std::string directoryToEncrypt("resources/data/");

    // Creation of a file with data/ directory.
    archiver.createFile(outputFile, directoryToEncrypt);
    // Now our data are archived in data.bin.

    // We are looking for the file through the file.
    std::vector<char> data = archiver.loadFile(outputFile, "log.txt");

    // We open a file and write it in it.
    file.open("output.txt",std::ios::binary);

    file.write(&data[0], data.size());

    file.close();
}
