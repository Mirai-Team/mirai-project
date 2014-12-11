#ifndef ENCRYPTION_HPP_INCLUDED
#define ENCRYPTION_HPP_INCLUDED

#include <string>
#include <fstream>

/** @file Encryption.hpp
 * This file defines various functions and variables for encrypting.
 */

namespace mp
{
    void ScrambleKey(std::string &input);
    void CryptBuffer(std::string &key, std::string &buffer);
}

#endif // ENCRYPTION_HPP_INCLUDED
