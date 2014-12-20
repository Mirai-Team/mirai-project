#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

#include "MiraiProject/util/files_functions.hpp"

using namespace std;

int mp::get_file_size(string filename)
{
    streampos filepos;

    ifstream temp_file(filename);

    //Move cursor to the end and read filepos which is the filesize.
    temp_file.seekg (0, ios::end);
    filepos = temp_file.tellg();

    temp_file.close();

    return static_cast<int>(filepos);

}
