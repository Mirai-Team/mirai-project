#ifndef ENCRYPT_FUNCTION_HPP_INCLUDED
#define ENCRYPT_FUNCTION_HPP_INCLUDED

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

/** @file encrypt_functions.hpp
 * \brief This file define basic encryption functions
 */

namespace mp
{
    /** \brief Encrypt the key with a NOT logic gates.
	 *
     * \param key : the non-encrypted key.
	 *
     * \return the encrypted key.
     */
    std::string encryptKey(std::string key);

    /** \brief Encrypt the given data with the given key.
	 *
     * The nth character from the data is modified by a  logic XOR 
	 * with the (n MOD key_length)th character from the key.
	 *
	 * \param key : the key.
	 * \param data : the data.
	 *
	 * \return the encrypted data.
	 */
    std::string encryptData(std::string key, std::string data);
}

#endif // ENCRYPT_FUNCTION_INCLUDED
