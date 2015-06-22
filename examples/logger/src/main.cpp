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

#include <MiraiProject/util/Logger.hpp>
#include <MiraiProject/util/MultiStream.hpp>

int main()
{
    std::ofstream myfile("example.txt", std::ios::out);

    mp::MultiStream streams({ myfile.rdbuf(), std::cout.rdbuf() });

    mp::Logger logger(&streams);

    logger << mp::Logger::priorityInfo << "Hello world" << std::endl;
    logger << mp::Priority("My prio") << "This is written in a file and printed in a terminal" << std::endl;

    logger << mp::Logger::priorityInfo << "This message" << std::endl
           << "\t is written on two lines." << std::endl;
}
