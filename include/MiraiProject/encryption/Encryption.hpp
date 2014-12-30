#ifndef ENCRYPTION_HPP_INCLUDED
#define ENCRYPTION_HPP_INCLUDED

#include <iostream>
#include <string>
#include <boost/filesystem.hpp>
#include <vector>

/**
 * \file Encryption.hpp
 * \brief A file which contains the class Encryption definition.
 *
 */
 
namespace mp {

	/** \class Encryption
	* \brief Encryption system
	*
	* 	Contains some methods to encrypt and read files.
	*/
    class Encryption
    {
        public:
            /** \brief Class Constructor. Set and encrypt the key
             *
             * \param key : A string who contains the key
             *
             */
            Encryption(std::string key);
            
            virtual ~Encryption();

            /** \brief Encrypt the file
             *
             * \param file : Path to file.
             * \return Return the whole file encrypted
             *
             */
            std::string encryptFile(std::string file);

            /** \brief Load a file in a encrypted pack.
             *
             * \param inputFile : File to parse
             * \param targetFile : The Target File
             * \return The decrypted file
             *
             */
            std::string loadFile(std::string inputFile, std::string targetFile);

            /** \brief A function to create a file encrypted
             *
             * \param outputFile : Path of the output file.
             * \param directory : Directory to encrypt.
             *
             */
            bool createFile(std::string outputFile, boost::filesystem::path directory);


        private:

            /** \brief Write the header (used in create_file)
            *  \return True if success else false.
            *
            */
            bool writeHeader();

            /** \brief Write the data (used in create_file)
            *  \return True if success else false.
            *
            */
            bool writeData();

            std::string key_;
            std::string outputFile_;
            std::vector<long int>offset_;
            std::vector<std::string>fileNames_;


    };
}

#endif // ENCRYPTION_HPP_INCLUDED
