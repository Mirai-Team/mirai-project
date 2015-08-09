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

#ifndef TEXTBOX_HPP_INCLUDED
#define TEXTBOX_HPP_INCLUDED

#include <memory>

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

#include "MiraiProject/gui/ClickableWidget.hpp"
#include "MiraiProject/gui/priv/Cursor.hpp"

namespace mp
{
    namespace
    {
        enum Direction
        {
            LEFT,
            RIGHT,
            UP,
            DOWN,
            START,
            END,
            STARTL,
            ENDL
        };
    }

    class TextBox : public ClickableWidget
    {
        public:
            TextBox(float maxWidth=0, float maxHeight=0);

            void update(const sf::Vector2i mousePosition);

            void click();

            /////////////
            // Setters //
            /////////////

            void setNormalTexture(const std::shared_ptr<sf::Texture> &texture);

            void setHoverTexture(const std::shared_ptr<sf::Texture> &texture);

            void setFocusTexture(const std::shared_ptr<sf::Texture> &texture);

            void setFont(const sf::Font& font);

            void setCharacterSize(const unsigned int size);

            void setTextPos(const float& x, const float& y);

            void setTextPos(const sf::Vector2f& position);

            void setCursorPos(const size_t& pos);

            void hideCursor();

            void showCursor();

            void toggleCursor();

            void setCursorColor(const sf::Color& color);

            void moveCursor(Direction direction);

            void enableMultiline();

            void disableMultiline();

            void focus();

            void unfocus();

            /* Set maximun text lengh. 0 = no limit. */
            void setMaxSize(const size_t& size);

            void handleInput(const sf::Event& event);

            void setString(const sf::String& text);

            /* Add text at cursor position */
            void addString(const sf::String& text);

            void insertText(const size_t& position, const sf::String& text);

            void appendText(const sf::String& text);

            void prependText(const sf::String& text);

            void deleteText(const size_t& pos, const size_t& n);

            void setMaxWidth(const float& width);

            void setMaxHeight(const float& height);

            /////////////
            // Getters //
            /////////////

            unsigned int getCharacterSize() const;

            const size_t& getCursorPos() const;

            const bool& cursorIsVisible() const;

            const sf::Color& getCursorColor() const;

            const bool& multilineIsEnabled() const;

            const bool& isFocused() const;

            const size_t& getMaxSize() const;

            const sf::String& getString() const;

            const float& getMaxWidth() const;

            const float& getMaxHeight() const;

        private:
            virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

            void updateCursorSize();

            void updateCursorPos();

            bool cursorVisible_;
            bool multilineEnabled_;
            bool focused_;
            bool hScroll_;
            bool vScroll_;

            size_t nFirstVisible_; // First visible character index.
            size_t cursorPos_;
            size_t maxSize_;

            std::shared_ptr<sf::Texture> textureNormal_;
            std::shared_ptr<sf::Texture> textureHover_;
            std::shared_ptr<sf::Texture> textureFocus_;

            float m_maxWidth;
            float m_maxHeight;

            sf::Text text_;
            mp::Cursor cursor_;
    };
}

#endif // TEXTBOX_HPP_INCLUDED
