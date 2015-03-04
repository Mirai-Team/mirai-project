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

#ifndef CLICKABLE_WIDGET_HPP_INCLUDED
#define CLICKABLE_WIDGET_HPP_INCLUDED

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Window.hpp>

#include "MiraiProject/gui/Widget.hpp"

namespace mp 
{
    class ClickableWidget : public Widget
    {
        public:
            ClickableWidget();

            void setSize(sf::Vector2f size);

            void setMousePosition(sf::Vector2f position);

            void setCurrentTexture(const sf::Texture* texture);

            void setAutoHitBox(bool autoMode);

            sf::Vector2f getSize();

            virtual bool mouseOnWidget();

            bool onNonTransparent(bool safeMode = true);

            virtual bool isPressed();

            virtual bool isReleased();
            
        private:
            bool isPressed_;

            bool autoHitBox_;

            sf::Vector2f size_;

            sf::Vector2f mousePosition_;

            const sf::Texture * currentTexture_;
    };
}

#endif