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

#include <iostream>
#include <stdexcept>

#include "MiraiProject/gui/ClickableWidget.hpp"

mp::ClickableWidget::ClickableWidget() :    isPressed_ { },
                                            autoHitBox_ { true },
                                            size_ { },
                                            mousePosition_ { },
                                            currentTexture_ { }
{

}

void mp::ClickableWidget::setSize(sf::Vector2f size)
{
    size_= size;
}

void mp::ClickableWidget::setMousePosition(sf::Vector2f position)
{
    mousePosition_ = position;
}

void mp::ClickableWidget::setCurrentTexture(const sf::Texture* texture)
{
    currentTexture_ = texture;
}

void mp::ClickableWidget::setAutoHitBox(bool autoMode)
{
    autoHitBox_ = autoMode;
}

sf::Vector2f mp::ClickableWidget::getSize()
{
    return size_;
}

sf::Vector2f mp::ClickableWidget::getMousePosition()
{
    return mousePosition_;
}

bool mp::ClickableWidget::mouseOnWidget()
{
    sf::FloatRect rect(0, 0, getSize().x, getSize().y);

    // Order have an importance.
    if(getTransform().transformRect(rect).contains(mousePosition_) && onNonTransparent(false))
        return true;
    else
        return false;
}

bool mp::ClickableWidget::onNonTransparent(bool safeMode)
{
    if(autoHitBox_)
    {
        unsigned int x = static_cast<int>(mousePosition_.x);
        x -= static_cast<int>(Transformable::getPosition().x);

        unsigned int y = static_cast<int>(mousePosition_.y);
        y -= static_cast<int>(Transformable::getPosition().y);

        if(safeMode)
        {
            if(x > currentTexture_->getSize().x)
                x = 0;
            if(y > currentTexture_->getSize().y)
                y = 0;
        }

        sf::Color pixel_color = currentTexture_->copyToImage().getPixel(x, y);

        if(pixel_color != sf::Color::Transparent)
            return true;
        else
            return false;
    }
    else
        return true;
}

bool mp::ClickableWidget::isPressed()
{
    if(mouseOnWidget() && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
        isPressed_ = true;
        return true;
    }
    else
        return false;
}

bool mp::ClickableWidget::isReleased()
{
    if(isPressed_ && !isPressed())
    {
        isPressed_ = false;
        if(mouseOnWidget())
            return true;
        else
            return false;
    }
    else
        return false;
}