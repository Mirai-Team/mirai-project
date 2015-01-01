////////////////////////////////////////////////////////////
//
// MiraiProject
// Copyright (C) 2014-2015 CORTIER Benoît (benoit.cortier@gmail.com), BOULMIER Jérôme (jerome.boulmier@outlook.com)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
// you must not claim that you wrote the original software.
// If you use this software in a product, an acknowledgment
// in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
// and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

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
