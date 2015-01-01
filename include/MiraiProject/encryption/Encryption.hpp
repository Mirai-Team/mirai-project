#ifndef ENCRYPTION_HPP_INCLUDED
#define ENCRYPTION_HPP_INCLUDED

#include <iostream>
#include <string>
#include <boost/filesystem.hpp>
#include <vector>

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


    };
}

#endif // ENCRYPTION_HPP_INCLUDED
