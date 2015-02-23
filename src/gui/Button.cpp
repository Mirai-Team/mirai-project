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

#include "MiraiProject/gui/Button.hpp"

mp::Button::Button(sf::Window& window) :    ClickableWidget(window), 
                                            funct_ { },
                                            sprite_ { },
                                            normal_ { },
                                            hover_ { },
                                            down_ { }
{

}

void mp::Button::update()
{
    
    if(isPressed())
        sprite_ = &down_;
    else if(mouseOnWidget())
        sprite_ = &hover_;
    else
        sprite_ = &normal_;


    if(isReleased())
        funct_();
}

void mp::Button::setFunction(std::function<void()> funct)
{
    funct_ = funct;
}

void mp::Button::setNormalTexture(sf::Texture &texture)
{
    normal_.setTexture(texture);

    sprite_ = &normal_;

    sf::Vector2f size(texture.getSize());
    setSize(size);
}

void mp::Button::setHoverTexture(sf::Texture &texture)
{
    hover_.setTexture(texture);
}

void mp::Button::setDownTexture(sf::Texture &texture)
{
    down_.setTexture(texture);
}

void mp::Button::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(*sprite_, states);
}