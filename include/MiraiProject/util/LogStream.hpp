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

#ifndef LOGSTREAM_HPP_INCLUDED
#define LOGSTREAM_HPP_INCLUDED

#include <fstream>
#include <memory>
#include <mutex>
#include <sstream>
#include <string>

#include "MiraiProject/util/Logger.hpp"

/** @file LogStream.hpp
 * \brief This file define LogStream class.
 */

namespace mp
{
    class Logger;
    
    /** \class Logstream
     * \brief A class to manage input stream of Logger class.
     */
    class Logstream : public std::ostringstream
    {
        public:
            /** \brief Constructor.
             *
             * \param logger : a Logger object.
             * \param priority : a string which contains Priority name.
             */
            Logstream(Logger& logger, std::string priority);

            /** \brief Constructor.
             *
             * \param ls : a Logstream object.
             */

            Logstream(const Logstream& ls);

            /** \brief Destructor */
            ~Logstream();

        private:
            Logger&         logger_;
            std::string     priority_;
    };
}
#endif // LOGSTREAM_HPP_INCLUDED