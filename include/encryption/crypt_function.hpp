#ifndef CRYPT_FUNCTION_HPP_INCLUDED
#define CRYPT_FUNCTION_HPP_INCLUDED

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

/** @file crypt_function.hpp
 * This file define the basic crypt functions
 *
 */

namespace mp
{
    std::string crypt_key(std::string key);
    std::string crypt_data(std::string key, std::string data);

    void write_header(std::string output_file, std::vector<std::string> filename, std::string key);
    void write_data(std::string filename, std::vector<std::string> filenames, std::vector<long int>offset, std::string key);

    void parse_header(std::string filename, std::string targetFile, std::string key);
}

#endif // CRYPT_FUNCTION_INCLUDED