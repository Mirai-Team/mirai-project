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

#include <string>

#include <SFML/System/String.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "MiraiProject/gui/Widget.hpp"

namespace mp
{
    class Label : public Widget
    {
        public:
            Label();

            /////////////
            // Setters //
            /////////////

            void setFont(const sf::Font& font);

            void setText(std::string string);
            void setText(sf::String string);

            virtual void setPosition(sf::Vector2f position);
            virtual void setPosition(float x, float y);

            void setStyle(sf::Text::Style style);

            void setColor(sf::Color color);

            void setCharacterSize(unsigned int size);

            /////////////
            // Getters //
            /////////////

            const sf::Font* getFont() const;

            const sf::String& getText() const;

            sf::Uint32 getStyle() const;

            const sf::Color& getColor() const;

            unsigned int getCharacterSize() const;
            
        private:
            virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

            sf::Text text_;
    };
}
