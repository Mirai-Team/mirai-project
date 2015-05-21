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

#include "MiraiProject/gui/CheckBox.hpp"

mp::CheckBox::CheckBox()
    : isChecked_ { false }
    , funct_ { nullptr }
    , activeTexture_ { }
    , checkedTexture_ { }
    , normalTexture_ { }
    , activeHoverTexture_ { }
    , hoverCheckedTexture_ { }
    , hoverTexture_ { }
    , activeDownTexture_ { }
    , downCheckedTexture_ { }
    , downTexture_ { }
{

}

void mp::CheckBox::setNormalTexture(const std::shared_ptr<sf::Texture> &texture)
{
    normalTexture_ = texture;

    if (!isChecked_)
        activeTexture_ = texture;
}

void mp::CheckBox::setCheckedTexture(const std::shared_ptr<sf::Texture> &texture)
{
    checkedTexture_ = texture;

    if (isChecked_)
        activeTexture_ = texture;
}

void mp::CheckBox::setHoverTexture(const std::shared_ptr<sf::Texture> &texture)
{
    hoverTexture_ = texture;

    if (!isChecked_)
        activeHoverTexture_ = texture;
}

void mp::CheckBox::setCheckedHoverTexture(const std::shared_ptr<sf::Texture> &texture)
{
    hoverCheckedTexture_ = texture;

    if (isChecked_)
        activeHoverTexture_ = texture;
}

void mp::CheckBox::setDownTexture(const std::shared_ptr<sf::Texture> &texture)
{
    downTexture_ = texture;

    if (!isChecked_)
        activeDownTexture_ = texture;
}

void mp::CheckBox::setCheckedDownTexture(const std::shared_ptr<sf::Texture> &texture)
{
    downCheckedTexture_ = texture;

    if (isChecked_)
        activeDownTexture_ = texture;
}

void mp::CheckBox::setFunction(std::function<void()> funct)
{
    funct_ = funct;
}

void mp::CheckBox::setChecked(bool state)
{
    isChecked_ = state;
}

bool mp::CheckBox::isChecked() const
{
    return isChecked_;
}

void mp::CheckBox::update(sf::Vector2i mousePosition)
{
    if(!isEnabled())
        return;

    setMousePosition(sf::Vector2f(mousePosition));

    if(isPressed() && activeDownTexture_ != nullptr)
    {
        setCurrentTexture(std::const_pointer_cast<const sf::Texture>(activeDownTexture_));
    }
    else if(mouseOnWidget() && activeHoverTexture_ != nullptr)
    {
        setCurrentTexture(std::const_pointer_cast<const sf::Texture>(activeHoverTexture_));
    }
    else
    {
        setCurrentTexture(std::const_pointer_cast<const sf::Texture>(activeTexture_));
    }

    if(isReleased())
    {
        onClick();

        if (funct_)
            funct_();
    }
}

void mp::CheckBox::onClick()
{
    if (isChecked_)
    {
        activeTexture_ = normalTexture_;

        if (downTexture_ != nullptr)
            activeDownTexture_ = downTexture_;

        if (hoverTexture_ != nullptr)
            activeHoverTexture_ = hoverTexture_;

        isChecked_ = false;
    }
    else
    {
        activeTexture_ = checkedTexture_;

        if (downCheckedTexture_ != nullptr)
            activeDownTexture_ = downCheckedTexture_;

        if (hoverCheckedTexture_ != nullptr)
            activeHoverTexture_ = hoverCheckedTexture_;

        isChecked_ = true;
    }
}
