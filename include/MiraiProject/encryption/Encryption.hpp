#ifndef ENCRYPTION_HPP_INCLUDED
#define ENCRYPTION_HPP_INCLUDED

#include <iostream>
#include <string>
#include <boost/filesystem.hpp>
#include <vector>

namespace mp {

    class Encryption
    {
        public:
            /** \brief Class Constructor. Set and encrypt the key
             *
             * \param key A string who contains the key
             *
             */

            Encryption(std::string key);
            virtual ~Encryption();

            /** \brief Encrypt the file
             *
             * \param file Path to file.
             * \return Return the whole file encrypted
             *
             */
            std::string encrypt_file(std::string file);

            /** \brief Load a file in a encrypted pack.
             *
             * \param inputFile File to parse
             * \param targetFile The Target File
             * \return The file decrypted
             *
             */
            std::string load_file(std::string inputFile, std::string targetFile);

            /** \brief A function to create a file encrypted
             *
             * \param outputFile Path of the output file.
             * \param directory Directory to encrypt.
             *
             */
            bool create_file(std::string outputFile, boost::filesystem::path directory);


        private:

            /** \brief Write the header (used in create_file)
            *  \return True if success else false.
            *
            */
            bool write_header();

            /** \brief Write the data (used in create_file)
            *  \return True if success else false.
            *
            */
            bool write_data();

            std::string _key;
            std::string _outputFile;
            std::vector<long int>_offset;
            std::vector<std::string>_filenames;


    };
}

#endif // ENCRYPTION_HPP_INCLUDED
