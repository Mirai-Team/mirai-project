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
#include <vector>
#include <sstream>

#include <boost/filesystem.hpp>

#include "MiraiProject/util/FilesUtilities.hpp"

using namespace std;
using namespace boost::filesystem;

vector<string> mp::filesUtilities::listFiles(path directory, bool recursive)
{
    vector<string> filesPaths;
    vector<string> tempFilesPaths;
    directory_iterator end_itr;

    // Cycle through the directory
    for (directory_iterator itr(directory); itr != end_itr; ++itr)
    {
        // If it's not a directory, add it in filesPaths.
        if (is_regular_file(itr->path()))
		{
            filesPaths.push_back(itr->path().string());
        }
        else if(recursive && is_directory(itr->path()))
        {
            // Else we start another cycle through this directory if we want all files recursively.
            tempFilesPaths = filesUtilities::listFiles(itr->path(), true);
            filesPaths.insert(filesPaths.end(), tempFilesPaths.begin(), tempFilesPaths.end());
        }

    }
	
    return filesPaths;
}
