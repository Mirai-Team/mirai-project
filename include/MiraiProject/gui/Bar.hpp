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

#ifndef BAR_HPP
#define BAR_HPP

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "MiraiProject/gui/Widget.hpp"

namespace mp
{
    class Bar : public Widget
    {
    public:

        enum Orientation
        {
            HORIZONTAL,
            VERTICAL
        };

        Bar();

        void                setTexture(const std::shared_ptr<sf::Texture>& texture);

        void                setOrientation(Bar::Orientation orientation);

        void                setRatio(float ratio);

        void                setMin(float value);

        void                setMax(float value);

        void                setValue(float value);

        void                setSize(sf::Vector2u size);

        float               getRatio() const;

        float               getMin() const;

        float               getMax() const;

        float               getValue() const;

        Bar::Orientation    getOrientation() const;

    private:
        void                update();

        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

        float               ratio_;

        float               value_;
        float               min_;
        float               max_;

        int                 fillPart_;

        Orientation         orientation_;

        sf::Sprite          fillsprite_;
    };
}

#endif // BAR_HPP
