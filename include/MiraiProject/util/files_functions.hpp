#ifndef FILE_FUNCTIONS_HPP_INCLUDED
#define FILE_FUNCTIONS_HPP_INCLUDED

#include <vector>
#include <string>
#include <boost/filesystem.hpp>

/** @file files_functions.hpp
 * \brief This file define various functions to manipulate files in order to keep a
 *        cross-platform library.
 */

namespace mp
{
    /** \brief List files in a directory.
     * 
     * \param directory : path of the directory
	 * \param recursive : true to search in all subdirectories. 
     * 
     * \return A std::vector<std::string> who contains files paths.
     */
    std::vector<std::string> listFiles(boost::filesystem::path directory, bool recursive=false);
}

#endif // FILE_FUNCTIONS_HPP_INCLUDED
