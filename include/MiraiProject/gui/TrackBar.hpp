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

#ifndef TRACKBAR_HPP_INCLUDED
#define TRACKBAR_HPP_INCLUDED

#include <memory>

#include <SFML/Graphics/Sprite.hpp>

#include "MiraiProject/gui/ClickableWidget.hpp"

namespace mp
{

class TrackBar : public ClickableWidget
{
public:
    TrackBar();

    void update(const sf::Vector2i& mousePosition);

    void setAcceptFloat(const bool& value);

    void setValue(const float& value);

    void setMin(const float& min);

    void setMax(const float& max);

    void setExtremPos1(const sf::Vector2f& pos);

    void setExtremPos2(const sf::Vector2f& pos);

    void setNormalTexture(const std::shared_ptr<sf::Texture>& texture);

    void setHoverTexture(const std::shared_ptr<sf::Texture>& texture);

    void setDownTexture(const std::shared_ptr<sf::Texture>& texture);

    const bool& isAcceptingFloat();

    const float& getValue();

    int getRoundedValue();

    const float& getMin();

    const float& getMax();

    const sf::Vector2f& getExtremPos1();

    const sf::Vector2f& getExtremPos2();

private:
    bool m_acceptFloat;

    float m_value;
    float m_min;
    float m_max;

    sf::Vector2f m_extremPos1;
    sf::Vector2f m_extremPos2;

    std::shared_ptr<sf::Texture> m_normal;
    std::shared_ptr<sf::Texture> m_hover;
    std::shared_ptr<sf::Texture> m_down;
};

}

#endif
