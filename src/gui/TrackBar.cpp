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

#include "MiraiProject/gui/TrackBar.hpp"

mp::TrackBar::TrackBar()
    : m_acceptFloat { true }

    , m_value { 0 }
    , m_min { 0 }
    , m_max { 0 }

    , m_extremPos1 { 0, 0 }
    , m_extremPos2 { 0, 0 }

    , m_normal { }
    , m_hover { }
    , m_down { }
{

}

void mp::TrackBar::update(const sf::Vector2i& mousePosition)
{
    if (!isEnabled())
        return;

    setMousePosition(sf::Vector2f(mousePosition));

    if (isPressed()) {
        setCurrentTexture(std::const_pointer_cast<const sf::Texture>(m_down));

        float newVal;
        if (fabs(m_extremPos2.x - m_extremPos1.x) > fabs(m_extremPos2.y - m_extremPos1.y)) {
            newVal = m_min + ((getMousePosition().x - m_extremPos1.x) / (m_extremPos2.x - m_extremPos1.x)) * (m_max - m_min);
        }
        else {
            newVal = m_min + ((getMousePosition().y - m_extremPos1.y) / (m_extremPos2.y - m_extremPos1.y)) * (m_max - m_min);
        }

        if (m_acceptFloat) {
            setValue(newVal);
        }
        else {
            setValue(static_cast<float>(static_cast<int>(newVal)));
        }
    }
    else if (mouseOnWidget()) {
        setCurrentTexture(std::const_pointer_cast<const sf::Texture>(m_hover));
    }
    else {
        setCurrentTexture(std::const_pointer_cast<const sf::Texture>(m_normal));
    }
}

void mp::TrackBar::setAcceptFloat(const bool& value)
{
    m_acceptFloat = value;
}

void mp::TrackBar::setValue(const float& value)
{
    m_value = value;

    if (m_value > m_max) {
        m_value = m_max;
    }
    else if (m_value < m_min) {
        m_value = m_min;
    }

    float valRatio { (m_value - m_min) / (m_max - m_min) };
    setPosition(m_extremPos1.x + (m_extremPos2.x - m_extremPos1.x) * valRatio,
                m_extremPos1.y + (m_extremPos2.y - m_extremPos1.y) * valRatio);
}

void mp::TrackBar::setMin(const float& min)
{
    m_min = min;

    if (m_value < m_min)
        m_value = m_min;
}

void mp::TrackBar::setMax(const float& max)
{
    m_max = max;

    if (m_value > m_max)
        m_value = m_max;
}

void mp::TrackBar::setExtremPos1(const sf::Vector2f& pos)
{
    m_extremPos1 = pos;
}

void mp::TrackBar::setExtremPos2(const sf::Vector2f& pos)
{
    m_extremPos2 = pos;
}

void mp::TrackBar::setNormalTexture(const std::shared_ptr<sf::Texture>& texture)
{
    m_normal = texture;
}

void mp::TrackBar::setHoverTexture(const std::shared_ptr<sf::Texture>& texture)
{
    m_hover = texture;
}

void mp::TrackBar::setDownTexture(const std::shared_ptr<sf::Texture>& texture)
{
    m_down = texture;
}

const bool& mp::TrackBar::isAcceptingFloat()
{
    return m_acceptFloat;
}

const float& mp::TrackBar::getValue()
{
    return m_value;
}

int mp::TrackBar::getRoundedValue()
{
    return static_cast<int>(m_value + 0.5f);
}

const float& mp::TrackBar::getMin()
{
    return m_min;
}

const float& mp::TrackBar::getMax()
{
    return m_max;
}

const sf::Vector2f& mp::TrackBar::getExtremPos1()
{
    return m_extremPos1;
}

const sf::Vector2f& mp::TrackBar::getExtremPos2()
{
    return m_extremPos2;
}

