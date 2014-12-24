#ifndef FILE_FUNCTIONS_HPP_INCLUDED
#define FILE_FUNCTIONS_HPP_INCLUDED

#include <vector>
#include <string>
#include <boost/filesystem.hpp>

/** @file files_functions.hpp
 * This file defines various functions to manipulate files in order to keep a
 * cross-platform library.
 */

namespace mp
{
    /** \brief Make a list of the files in a directory.
     *
     * \param directory Path of the directory
     * \return A vector who contains the list of directory's files.
     *
     */
    std::vector<std::string> list_file(boost::filesystem::path directory);
}

#endif // FILE_FUNCTIONS_HPP_INCLUDED
