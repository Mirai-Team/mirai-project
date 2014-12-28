#ifndef ENCRYPT_FUNCTION_HPP_INCLUDED
#define ENCRYPT_FUNCTION_HPP_INCLUDED

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

/** @file encrypt_functions.hpp
 * This file define the basic crypt functions
 *
 */

namespace mp
{
    /** \brief Encrypt the key with a NOT door
    * \param key : The key unencrypted.
    * \return The key encrypted
    */
    std::string encryptKey(std::string key);

    /** \brief Encrypt the data with a XOR etween the key MOD length() and data.*/
    std::string encryptData(std::string key, std::string data);
}

#endif // ENCRYPT_FUNCTION_INCLUDED
