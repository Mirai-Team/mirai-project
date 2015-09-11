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
#include <cmath>
#include <limits>

namespace
{
    bool floatEqual(const double a, const double b)
    {
        return fabs (a - b) <= ((fabs (a) > fabs (b) ? fabs (b) : fabs (a)) *
            std::numeric_limits<double>::epsilon ());
    }
}

mp::Bar::Bar()
    : ratio_ { 1.f }
    , value_ { }
    , fillPart_ {}
    , orientation_ { Bar::Orientation::HORIZONTAL }
    , fillsprite_ {}
{
}

void mp::Bar::setTexture(const std::shared_ptr<sf::Texture>& texture)
{
    texture->setRepeated(true);
    fillsprite_.setTexture(*texture);

    update();
}

void mp::Bar::setOrientation(Bar::Orientation orientation)
{
    orientation_ = orientation;
    update();
}

void mp::Bar::setRatio(float ratio)
{
    ratio_ = ratio;

    if (ratio > 1.f)
    {
        ratio_ = 1.f;
    }
    else if (ratio < 0.f)
    {
        ratio_ = 0.f;
    }

    value_ = ratio_ * (max_ - min_);

    update();
}

void mp::Bar::setValue(float value)
{
    value_ = value;

    if (value_ > max_)
    {
        value_ = max_;
    }
    else if (value_ < min_)
    {
        value_ = min_;
    }

    updateRatio();
    update();
}

void mp::Bar::setMin(float value)
{
    // Seg fault possible si max_ = min_.
    min_ = value;

    if (value_ < min_)
        setValue(min_);

    updateRatio();
    update();
}
void mp::Bar::setMax(float value)
{
    max_ = value;

    if (value_ > max_)
        setValue(max_);

    updateRatio();
    update();
}

void mp::Bar::setSize(sf::Vector2u size)
{
    Widget::setSize(size);
    updateRatio();
    update();
}

float mp::Bar::getRatio() const
{
    return ratio_;
}

float mp::Bar::getMin() const
{
    return min_;
}

float mp::Bar::getMax() const
{
    return max_;
}

float mp::Bar::getValue() const
{
    return value_;
}

mp::Bar::Orientation mp::Bar::getOrientation() const
{
    return orientation_;
}

void mp::Bar::update()
{
    if (orientation_ == Bar::Orientation::HORIZONTAL)
    {
        fillPart_ = static_cast<int>(ratio_ * static_cast<float>(getSize().x));
        fillsprite_.setTextureRect(sf::IntRect(0,0, fillPart_, getSize().y));
    }
    else
    {
        fillPart_ = static_cast<int>(ratio_ * static_cast<float>(getSize().y));
        fillsprite_.setTextureRect(sf::IntRect(0,0, getSize().x, fillPart_));
    }
}

void mp::Bar::updateRatio()
{
    ratio_ = value_ / (max_ - min_);
}

void mp::Bar::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(fillsprite_, states);
}

