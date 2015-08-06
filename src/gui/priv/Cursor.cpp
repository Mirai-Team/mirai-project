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

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Color.hpp>

#include "MiraiProject/gui/priv/Cursor.hpp"

mp::Cursor::Cursor(const float& width, const float& height)
    : m_visible{ true }
    , m_rect{ {width, height} }
{

}

void mp::Cursor::setPosition(const sf::Vector2f& pos)
{
    m_rect.setPosition(pos);
}

void mp::Cursor::setSize(const sf::Vector2f& size)
{
    m_rect.setSize(size);
}

void mp::Cursor::setColor(const sf::Color& color)
{
    m_rect.setFillColor(color);
}

void mp::Cursor::setVisible(const bool& value)
{
    m_visible = value;
}

const sf::Vector2f& mp::Cursor::getPosition() const
{
    return m_rect.getPosition();
}

const sf::Vector2f& mp::Cursor::getSize() const
{
    return m_rect.getSize();
}

const sf::Color& mp::Cursor::getColor() const
{
    return m_rect.getFillColor();
}

const bool& mp::Cursor::getVisible() const
{
    return m_visible;
}

void mp::Cursor::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (m_visible)
        target.draw(m_rect, states);
}

