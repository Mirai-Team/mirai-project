#ifndef CRYPT_FUNCTION_HPP_INCLUDED
#define CRYPT_FUNCTION_HPP_INCLUDED

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

/** @file crypt_function.hpp
 * This file define the basic crypt functions.
 */

namespace mp
{
    std::string crypt_key(std::string key);
    std::string crypt_data(std::string key, std::string data);
}

#endif // CRYPT_FUNCTION_INCLUDED
