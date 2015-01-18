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

#ifndef AUTORESMANAGER_HPP_INCLUDED
#define AUTORESMANAGER_HPP_INCLUDED

#include <memory>
#include <map>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "MiraiProject/resourcesManagers/BaseResManager.hpp"

/** \file AutoResManager.hpp
 * \brief This file contains AutoResManager class definition.
 */

namespace mp
{
    /** \class AutoResManager
     * \brief A class to automatically handle resources (images and sounds).
     * Though, you still have to clean resources using clean method.
     */

    class AutoResManager : public BaseResManager
    {
        public:
            /** \brief Automatically load the texture if necessary and return it.
             *
             * \param fileName : the file name related to the wanted texture.
             *
             * \return the texture related to the given file name.
             */
            std::shared_ptr<sf::Texture> getTexture(const std::string &fileName);
            
            /** \brief Automatically load the sound buffer if necessary and return it.
             *
             * \param fileName : the file name related to the wanted sound buffer.
             *
             * \return the sound buffer related to the given file name.
             */
            std::shared_ptr<sf::SoundBuffer> getSoundBuffer(const std::string &fileName);

            /** \brief Automatically load the font if necessary and return it.
             *
             * \param fileName : the file name related to the wanted font.
             *
             * \return the font related to the given file name.
             */
            std::shared_ptr<sf::Font> getFontBuffer(const std::string &fileName);
    };
}

#endif // AUTORESMANAGER_HPP_INCLUDED