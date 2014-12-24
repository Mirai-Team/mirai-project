#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

#include <boost/filesystem.hpp>

#include "MiraiProject/util/files_functions.hpp"
#include "MiraiProject/util/log.hpp"

using namespace std;
using namespace boost::filesystem;

vector<string> mp::list_file(path directory)
{
    vector<string> filepath;
    vector<string> temp;
    directory_iterator end_itr;

    // cycle through the directory
    for (directory_iterator itr(directory); itr != end_itr; ++itr)
    {
        // If it's not a directory, add it in filepath.
        if (is_regular_file(itr->path())) {
            filepath.push_back(itr->path().string());
        }
        else if(is_directory(itr->path()))
        {
            //Else we start a cycle through this directory.
            temp = list_file(itr->path());
            filepath.insert(filepath.end(), temp.begin(), temp.end() );
        }

    }
    return filepath;
}
