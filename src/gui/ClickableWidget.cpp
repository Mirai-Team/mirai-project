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

#include "MiraiProject/gui/ClickableWidget.hpp"

mp::ClickableWidget::ClickableWidget() :    isPressed_ { },
                                            size_ { }
{

}

void mp::ClickableWidget::setSize(sf::Vector2f size)
{
    size_= size;
}

sf::Vector2f mp::ClickableWidget::getSize()
{
    return size_;
}

bool mp::ClickableWidget::mouseOnWidget()
{
    sf::Vector2f mousePosition(sf::Mouse::getPosition());
    sf::FloatRect rect(getPosition().x, getPosition().y, getSize().x, getSize().y);
    if(getTransform().transformRect(rect).contains(mousePosition))
        return true;
    else
        return false;
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