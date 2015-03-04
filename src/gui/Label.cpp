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

#include "MiraiProject/gui/Label.hpp"

mp::Label::Label() : text_ { }
{

}

void mp::Label::setFont(const sf::Font& font)
{
    text_.setFont(font);

    text_.setString(getText());
}

void mp::Label::setText(std::string string)
{
    text_.setString(string);
}

void mp::Label::setText(sf::String string)
{
    text_.setString(string);
}

void mp::Label::setPosition(sf::Vector2f position)
{
    Transformable::setPosition(position.x, position.y);

    text_.setPosition(position.x - text_.getLocalBounds().left, position.y - text_.getLocalBounds().top);
}

void mp::Label::setPosition(float x, float y)
{
    Transformable::setPosition(x, y);

    text_.setPosition(x - text_.getLocalBounds().left, y - text_.getLocalBounds().top);
}

void mp::Label::setStyle(sf::Text::Style style)
{
    text_.setStyle(style);
}

void mp::Label::setColor(sf::Color color)
{
    text_.setColor(color);
}

void mp::Label::setCharacterSize(unsigned int size)
{
    text_.setCharacterSize(size);

    setPosition(getPosition());
}

const sf::Font* mp::Label::getFont() const
{
    return text_.getFont();
}

const sf::String& mp::Label::getText() const
{
    return text_.getString();
}

sf::Uint32 mp::Label::getStyle() const
{
    return text_.getStyle();
}

const sf::Color& mp::Label::getColor() const
{
    return text_.getColor();
}

unsigned int mp::Label::getCharacterSize() const
{
    return text_.getCharacterSize();
}

void mp::Label::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    if(isVisible())
        target.draw(text_, states);
}