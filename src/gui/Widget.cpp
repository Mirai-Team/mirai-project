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

#include "MiraiProject/gui/Widget.hpp"

mp::Widget::Widget() : sprite_ { },
                       isEnabled_ { true },
                       size_ { }
{

}

void mp::Widget::setCurrentTexture(std::shared_ptr<const sf::Texture> texture)
{
    sprite_.setTexture(*texture);
    setSize(texture->getSize());
}

void mp::Widget::setSize(sf::Vector2u size)
{
    size_= size;
}

void mp::Widget::enable()
{
    isEnabled_ = true;
}

void mp::Widget::disable()
{
    isEnabled_ = false;
}

std::shared_ptr<const sf::Texture> mp::Widget::getTexture() const
{
    return std::make_shared<const sf::Texture>(*sprite_.getTexture());
}

sf::Vector2u mp::Widget::getSize() const
{
    return size_;
}

bool mp::Widget::isEnabled() const
{
    return isEnabled_;
}

void mp::Widget::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite_, states);
}

