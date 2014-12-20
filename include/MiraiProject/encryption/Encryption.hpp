#ifndef ENCRYPTION_HPP_INCLUDED
#define ENCRYPTION_HPP_INCLUDED

namespace mp {

    class Encryption
    {
        public:
            Encryption(std::string key, std::string data);
            virtual ~Encryption();

            /** \brief Crypt the file
             *
             * \param path to file.
             * \return return the whole file encrypted
             *
             */
            std::string crypt_file(std::string file);

            /** \brief parse the header in order to find the target file.
             *
             * \param File to parse
             * \param The Target File
             * \return The file decrypted
             *
             */
            std::string parse_header(std::string inputFile, std::string targetFile);

            /** \brief A function to create a file encrypted
             *
             * \param Path of the output file.
             * \param A vector which contains the files' paths
             *
             */
            void create_file(std::string outputFile, std::vector<std::string> filenames);
            void write_header();
            void write_data();

        private:

            std::string _key;
            std::string _data;
            std::string _targetFile;
            std::string _outputFile;
            std::string _inputFile;
            std::vector<long int>_offset;
            std::vector<std::string>_filenames;


    };
}

#endif // ENCRYPTION_HPP_INCLUDED
