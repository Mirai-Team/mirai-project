#ifndef CRYPT_FUNCTION_HPP_INCLUDED
#define CRYPT_FUNCTION_HPP_INCLUDED

#include <string>
#include <fstream>

/** @file crypt_function.hpp
 * This file define the basic crypt functions.
 */

namespace mp
{
    std::string CryptKey(std::string key);
    std::string CryptData(std::string key, std::string data);
}

#endif // CRYPT_FUNCTION_INCLUDED
