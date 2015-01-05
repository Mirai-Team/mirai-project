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

#ifndef ENCRYPTION_HPP_INCLUDED
#define ENCRYPTION_HPP_INCLUDED

#include <iostream>
#include <string>
#include <boost/filesystem.hpp>
#include <vector>
#include <fstream>
#include <sstream>

#include "MiraiProject/util/Logger.hpp"

/** \file Encryption.hpp
 * \brief This file contains Encryption class definition.
 */
 
namespace mp {

	/** \class Encryption
	* \brief A class to encrypt files.
	*
	* Contains some methods to encrypt and read files.
	*/
    class Encryption
    {
        public:
            /** \brief Class Constructor. Set and encrypt the key.
			 * 
             * \param key : a string who contains the key.
             */
            Encryption(std::string key);
            
            virtual ~Encryption();

            /** \brief Encrypt the file.
             *
             * \param file : path to file.
             * 
             * \return the whole file content encrypted.
             */
            std::string encryptFile(std::string file);

            /** \brief Load a file from an encrypted pack.
             *
             * \param inputFile : file to parse.
             * \param targetFile : the target file.
             * 
             * \return the file content decrypted.
             */
            std::string loadFile(std::string inputFile, std::string targetFile);

            /** \brief A method to create an encrypted file.
             *
             * \param outputFile : path for the output file.
             * \param directory : directory to encrypt.
			 *
			 * \return true if the operation is a success.
             */
            bool createFile(std::string outputFile, boost::filesystem::path directory);
			
			/** \brief Encrypt the key with a NOT logic gates.
			 *
			 * \param key : the non-encrypted key.
			 *
			 * \return the encrypted key.
			 */
			static std::string encryptKey(std::string key);
			
			/** \brief Encrypt the given data with the given key.
			 *
			 * The nth character from the data is modified by a logic XOR 
			 * with the (n MOD key_length)th character from the key.
			 *
			 * \param key : the key.
			 * \param data : the data.
			 *
			 * \return the encrypted data.
			 */
			static std::string encryptData(std::string key, std::string data);

        private:

            /** \brief Write the header.
             * 
             * \return true if the operation is a success.
             */
            bool writeHeader();

            /** \brief Write the data.
             * 
             * \return true if the operation is a success.
             */
            bool writeData();

            std::string key_;
            std::string outputFile_;
            std::vector<long int>offset_;
            std::vector<std::string>fileNames_;
            
            Logger log_;


    };
}

#endif // ENCRYPTION_HPP_INCLUDED
