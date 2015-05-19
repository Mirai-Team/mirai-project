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

#include "MiraiProject/gui/Border.hpp"

mp::Border::Border() :  vertices_ { },
                        size_ { },
                        color_ { },
                        radius_ { },
                        pointCount_ { },
                        type_ { }
{

}

void mp::Border::createRectangle(float width, float height, sf::Color color)
{
    type_ = 1;
    color_ = color;
    size_.x = width;
    size_.y = height;

    vertices_.setPrimitiveType(sf::Lines);
    for(unsigned int i = 0; i < 4; i++)
    {
        switch(i)
        {
            case 0:
                vertices_.append(sf::Vertex(sf::Vector2f(0, 0), color_));
                vertices_.append(sf::Vertex(sf::Vector2f(0, size_.y), color_));
                break;
            case 1:
                vertices_.append(sf::Vertex(sf::Vector2f(0, size_.y), color_));
                vertices_.append(sf::Vertex(sf::Vector2f(size_.x, size_.y), color_));
                break;
            case 2:
                vertices_.append(sf::Vertex(sf::Vector2f(size_.x, size_.y), color_));
                vertices_.append(sf::Vertex(sf::Vector2f(size_.x, 0), color_));
                break;
            case 3:
                vertices_.append(sf::Vertex(sf::Vector2f(size_.x, 0), color_));
                vertices_.append(sf::Vertex(sf::Vector2f(0, 0), color_));
                break;
            default:
                break;
        }
    }
}

void mp::Border::createBlank(mp::Border::Edge edge, float width, float offset)
{
    if(type_ != 1)
        return;

    switch(edge)
    {
        case 0:
            vertices_[1] = sf::Vertex(sf::Vector2f(0, offset), color_);
            vertices_.append(sf::Vertex(sf::Vector2f(0, offset + width), color_));
            vertices_.append(sf::Vertex(sf::Vector2f(0, size_.y), color_));
            break;
        case 1:
            vertices_[3] = sf::Vertex(sf::Vector2f(offset, size_.y), color_);
            vertices_.append(sf::Vertex(sf::Vector2f(offset + width, size_.y), color_));
            vertices_.append(sf::Vertex(sf::Vector2f(size_.x, size_.y), color_));
            break;
        case 2:
            vertices_[4] = sf::Vertex(sf::Vector2f(size_.x, offset), color_);
            vertices_.append(sf::Vertex(sf::Vector2f(size_.x, offset + width), color_));
            vertices_.append(sf::Vertex(sf::Vector2f(size_.x, size_.y), color_));
            break;
        case 3:
            vertices_[6] = sf::Vertex(sf::Vector2f(offset, 0), color_);
            vertices_.append(sf::Vertex(sf::Vector2f(offset + width, 0), color_));
            vertices_.append(sf::Vertex(sf::Vector2f(size_.x, 0), color_));
            break;
        default:
            break;
    }
}

void mp::Border::setColor(sf::Color color)
{
    color_ = color;

    for(unsigned int i = 0; i < vertices_.getVertexCount(); i++)
        vertices_[i].color = color_;
}

void mp::Border::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(vertices_, states);
}