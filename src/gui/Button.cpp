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

#include "MiraiProject/gui/Button.hpp"

mp::Button::Button()
    : funct_ { nullptr }
    , normal_ { }
    , hover_ { }
    , down_ { }
{

}

void mp::Button::update(sf::Vector2i mousePosition)
{
    if (!isEnabled())
        return;

    mp::ClickableWidget::update(mousePosition);

    if (!isPressed())
    {
        if(mouseOnWidget())
        {
            setCurrentTexture(std::const_pointer_cast<const sf::Texture>(hover_));
        }
        else
        {
            setCurrentTexture(std::const_pointer_cast<const sf::Texture>(normal_));
        }
    }
}

void mp::Button::setFunction(std::function<void()> funct)
{
    funct_ = funct;
}

void mp::Button::setNormalTexture(const std::shared_ptr<sf::Texture> &texture)
{
    normal_ = texture;
}

void mp::Button::setHoverTexture(const std::shared_ptr<sf::Texture> &texture)
{
    hover_ = texture;
}

void mp::Button::setDownTexture(const std::shared_ptr<sf::Texture> &texture)
{
    down_ = texture;
}

void mp::Button::onClick()
{
    setCurrentTexture(std::const_pointer_cast<const sf::Texture>(down_));
}

void mp::Button::onRelease()
{
    funct_();
}

