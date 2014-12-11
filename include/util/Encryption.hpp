#ifndef ENCRYPTION_HPP_INCLUDED
#define ENCRYPTION_HPP_INCLUDED

#include <string>
#include <fstream>

/** @file Encryption.hpp
 * This file defines various functions and variables for encrypting.
 */

using namespace std;

namespace mp
{
    void ScrambleKey(string &input);
    void CryptBuffer(string &key, string &buffer);
}

#endif // ENCRYPTION_HPP_INCLUDED
