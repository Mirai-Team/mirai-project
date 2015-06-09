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

#include "MiraiProject/gui/Bar.hpp"
#include <iostream>

mp::Bar::Bar()
    : value_ { 1.f }
    , fillPart_ {}
    , orientation_ { Bar::Orientation::HORIZONTAL }
    , fillsprite_ {}
{
}

void mp::Bar::setTexture(const std::shared_ptr<sf::Texture>& texture)
{
    texture->setRepeated(true);
    fillsprite_.setTexture(*texture);
    if (orientation_ == Bar::Orientation::HORIZONTAL)
    {
        fillPart_ = static_cast<int>(value_ * static_cast<float>(getSize().x));

        fillsprite_.setTextureRect(sf::IntRect(0,0, fillPart_, getSize().y));
    }
    else
    {
        fillPart_ = static_cast<int>(value_ * static_cast<float>(getSize().y));
        fillsprite_.setTextureRect(sf::IntRect(0,0, getSize().x, fillPart_));
    }
}


void mp::Bar::setOrientation(Bar::Orientation orientation)
{
    orientation_ = orientation;
    if (orientation_ == Bar::Orientation::HORIZONTAL)
    {
        fillPart_ = static_cast<int>(value_ * static_cast<float>(getSize().x));
        fillsprite_.setTextureRect(sf::IntRect(0,0, fillPart_, getSize().y));
    }
    else
    {
        fillPart_ = static_cast<int>(value_ * static_cast<float>(getSize().y));
        fillsprite_.setTextureRect(sf::IntRect(0,0, getSize().x, fillPart_));
    }
}

void mp::Bar::setValue(float value)
{
    value_ = value;

    if (value > 1.f)
        value_ = 1;
    else if (value < 0.f)
        value_ = 0.f;

    if (orientation_ == Bar::Orientation::HORIZONTAL)
    {
        fillPart_ = static_cast<int>(value_ * static_cast<float>(getSize().x));
        fillsprite_.setTextureRect(sf::IntRect(0,0, fillPart_, getSize().y));
    }
    else
    {
        fillPart_ = static_cast<int>(value_ * static_cast<float>(getSize().y));
        fillsprite_.setTextureRect(sf::IntRect(0,0, getSize().x, fillPart_));
    }
}

float mp::Bar::getValue() const
{
    return value_;
}

mp::Bar::Orientation mp::Bar::getOrientation() const
{
    return orientation_;
}

void mp::Bar::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(fillsprite_, states);
}
