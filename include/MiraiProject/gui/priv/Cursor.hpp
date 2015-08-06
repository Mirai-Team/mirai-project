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

#ifndef MP_CURSOR_HPP
#define MP_CURSOR_HPP value

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Color.hpp>

#include "MiraiProject/scene/Node.hpp"

namespace mp
{

class Cursor : public Node
{
public:
    Cursor(const float& width=1, const float& height=10);

    /////////////
    // Setters //
    /////////////

    void setPosition(const sf::Vector2f& newPos);

    void setSize(const sf::Vector2f& size);

    void setColor(const sf::Color& color);

    void setVisible(const bool& value);

    /////////////
    // Getters //
    /////////////

    const sf::Vector2f& getPosition() const;

    const sf::Vector2f& getSize() const;

    const sf::Color& getColor() const;

    const bool& getVisible() const;

private:
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

    bool m_visible;

    sf::RectangleShape m_rect;
};

}

#endif // MP_CURSOR_HPP

