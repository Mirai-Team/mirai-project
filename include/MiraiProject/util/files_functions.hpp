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
