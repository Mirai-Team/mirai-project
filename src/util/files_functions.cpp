#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

#include <boost/filesystem.hpp>

#include "MiraiProject/util/files_functions.hpp"
#include "MiraiProject/util/log.hpp"

using namespace std;
using namespace boost::filesystem;

vector<string> mp::listFile(path directory)
{
    vector<string> filePath;
    vector<string> temp;
    directory_iterator end_itr;

    // cycle through the directory
    for (directory_iterator itr(directory); itr != end_itr; ++itr)
    {
        // If it's not a directory, add it in filepath.
        if (is_regular_file(itr->path())) {
            filePath.push_back(itr->path().string());
        }
        else if(is_directory(itr->path()))
        {
            //Else we start a cycle through this directory.
            temp = listFile(itr->path());
            filePath.insert(filePath.end(), temp.begin(), temp.end() );
        }

    }
    return filePath;
}
