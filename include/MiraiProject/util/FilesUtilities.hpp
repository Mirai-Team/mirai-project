////////////////////////////////////////////////////////////
//
// MiraiProject
// Copyright (C) 2014-2015 CORTIER Benoît (benoit.cortier@gmail.com), BOULMIER Jérôme (jerome.boulmier@outlook.fr)
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

#ifndef FILE_FUNCTIONS_HPP_INCLUDED
#define FILE_FUNCTIONS_HPP_INCLUDED

#include <vector> // std::vector
#include <string> // std::string

#include <boost/filesystem.hpp> // boost::filesystem::path

/** @file files_functions.hpp
 * \brief This file define various functions to manipulate files or files related data to keep a
 *        cross-platform library.
 */

namespace mp
{
    /** \class filesUtilities
     * \brief A static class with various functions to manipulate files, or files related data.
     */

    class filesUtilities
    {
        public:
            /** \brief List files in a directory.
             *
             * \param directory : path of the directory
             * \param recursive : true to search in all subdirectories.
             *
             * \return a std::vector<std::string> who contains files paths.
             */
            static std::vector<std::string> listFiles(boost::filesystem::path directory, bool recursive=false);

            /** \brief Convert file path to unix-style file path.
             *
             * You can use it to make sure your file path works under windows and unix.
             *
             * \param filePath : the file path to convert.
             *
             * \return the converted file path.
             */
            static void convertToUnixFilePath(std::string* filePath);
    };

    /**
     * @brief Insert data in a file.
     *
     * @param outputPath : File in which the data are written.
     * @param offset : Where the data should be written.
     * @param data : Data which should be written.
     * @param dataSize : Data size.
     */
    void insertData(const std::string& outputPath,
        size_t offset,
        const void* data,
        size_t dataSize);

    void shiftData(const std::string& filePath,
        size_t offset,
        int shiftOffset);
}

#endif // FILE_FUNCTIONS_HPP_INCLUDED
