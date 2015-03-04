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

#ifndef TRANSFORMABLE_UTILITIES_HPP_INCLUDED
#define TRANSFORMABLE_UTILITIES_HPP_INCLUDED

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include "MiraiProject/animations/AnimatedSprite.hpp"

/** @file TransformableUtilities.hpp
 * \brief This file define various static functions to manipulate sf::Transformable into TransformableUtilities class.
 */

namespace mp
{
    /** \class TransformableUtilities
     * \brief A static class with various functions to manipulate sf::Transformable.
     */

    class TransformableUtilities
    {
        public:
            /** \brief Sets the sprite's origin to its center. 
             *
             * \param sprite : the sprite.
             */
            static void centerOrigin(sf::Sprite& sprite);

            /** \brief Sets the animated sprite's origin to its center. 
             *
             * \param sprite : the animated sprite.
             */
            static void centerOrigin(mp::AnimatedSprite& animatedSprite);

            /** \brief Sets the text's origin to its center. 
             *
             * \param text : the text.
             */
            static void centerOrigin(sf::Text& text);
    };
}

#endif // TRANSFORMABLE_UTILITIES_HPP_INCLUDED