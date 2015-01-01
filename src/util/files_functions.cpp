#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

#include <boost/filesystem.hpp>

#include "MiraiProject/util/files_functions.hpp"
#include "MiraiProject/util/log.hpp"

using namespace std;
using namespace boost::filesystem;

vector<string> mp::listFiles(path directory, bool recursive)
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
            tempFilesPaths = listFiles(itr->path(), true);
            filesPaths.insert(filesPaths.end(), tempFilesPaths.begin(), tempFilesPaths.end());
        }

    }
	
    return filesPaths;
}
