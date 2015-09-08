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

#include <stdexcept>

#include "MiraiProject/gui/ClickableWidget.hpp"

mp::ClickableWidget::ClickableWidget()
    : isPressed_ { false }
    , isMousePressed_ { false }
    , autoHitBox_ { true }
    , mousePosition_ { }
{

}

void mp::ClickableWidget::update(sf::Vector2i position)
{
    mousePosition_ = position;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
        if (mouseOnWidget() and !isMousePressed_ and !isPressed_)
        {
            onClick();
            isPressed_ = true;
        }

        isMousePressed_ = true;
    }
    else
    {
        if (isPressed_)
        {
            onRelease();
            isPressed_ = false;
        }

        isMousePressed_ = false;
    }
}

void mp::ClickableWidget::setAutoHitBox(bool autoMode)
{
    autoHitBox_ = autoMode;
}

sf::Vector2i mp::ClickableWidget::getMousePosition() const
{
    return mousePosition_;
}

bool mp::ClickableWidget::isPressed() const
{
    return isPressed_;
}

bool mp::ClickableWidget::mouseOnWidget() const
{
    sf::FloatRect rect(0, 0, static_cast<float>(getSize().x), static_cast<float>(getSize().y));

    // Order have an importance.
    if (getTransform().transformRect(rect).contains(sf::Vector2f(mousePosition_)) && onNonTransparent())
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool mp::ClickableWidget::onNonTransparent() const
{
    if (autoHitBox_)
    {
        unsigned int x = static_cast<int>(mousePosition_.x);
        x += static_cast<int>(getOrigin().x);
        x -= static_cast<int>(Transformable::getPosition().x);

        unsigned int y = static_cast<int>(mousePosition_.y);
        y += static_cast<int>(getOrigin().y);
        y -= static_cast<int>(Transformable::getPosition().y);

        sf::Color pixel_color = getTexture()->copyToImage().getPixel(x, y);

        if(pixel_color != sf::Color::Transparent)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return true;
    }
}

void mp::ClickableWidget::onClick()
{
}

void mp::ClickableWidget::onRelease()
{
}

