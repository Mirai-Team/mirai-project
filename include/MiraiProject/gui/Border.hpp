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

#ifndef BORDER_HPP_INCLUDED
#define BORDER_HPP_INCLUDED

#include <cmath>

#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "MiraiProject/gui/Widget.hpp"

namespace mp
{
    class Border : public Widget
    {
        public:
            enum Edge
            {
                Left = 0,
                Bottom,
                Right,
                Top,
            };

            Border();

            void createRectangle(float width, float height, sf::Color color = sf::Color::White);

            void createBlank(Edge corner, float width, float offset);

            void setColor(sf::Color color);
        private:
            virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

            sf::VertexArray vertices_;
            sf::Vector2f size_;
            sf::Color color_;

            float radius_;

            unsigned int pointCount_;

            short int type_;
    };
}

#endif