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

#include <cstdio>
#include <cstdlib>

#include "encryption.hpp"

using namespace boost::filesystem;
using namespace std;

int main(int argc, char **argv)
{
	if(argc < 3)
	{
		cout << "To crypt	: -c directory key outputFile" << endl;
		cout << "To decrypt	: -d inputFile key" << endl;
		
		return 0;
	}

	if(strcmp(argv[1],"-c")==0 and argv = 3)
	{
		path directory(argv[2]);
		encryptFiles(argv[3], directory, argv[4]);
	}
	else if(strcmp(argv[1],"-d")==0 and argc = 4)
		decryptFiles(argv[3], argv[2]);
	else
	{
		cout << "To crypt	: -c directory key outputFile" << endl;
		cout << "To decrypt	: -d inputFile key" << endl;
	}
	return 0;
}
