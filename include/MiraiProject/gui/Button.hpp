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

#ifndef BUTTON_HPP_INCLUDED
#define BUTTON_HPP_INCLUDED

#include <functional>
#include <memory>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "MiraiProject/gui/ClickableWidget.hpp"

namespace mp
{
    class Button : public ClickableWidget
    {
        public:
            Button(sf::Window& window);

            void update();

            void setFunction(std::function<void()> funct);

            void setNormalTexture(std::shared_ptr<sf::Texture> texture);

            void setHoverTexture(std::shared_ptr<sf::Texture> texture);

            void setDownTexture(std::shared_ptr<sf::Texture> texture);
        private:
            virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

            std::function<void()> funct_;

            sf::Sprite* sprite_;
            sf::Sprite normal_;
            sf::Sprite hover_;
            sf::Sprite down_;
    };
}

#endif