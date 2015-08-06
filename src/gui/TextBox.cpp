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

#include <SFML/Graphics/Font.hpp>

#include "MiraiProject/gui/TextBox.hpp"
#include "MiraiProject/gui/ClickableWidget.hpp"

mp::TextBox::TextBox() : textureNormal_ { },
                         textureHover_ { },
                         textureFocus_ { },

                         text_ { },

                         nFirstVisible_ { 0 },
                         cursorPos_ { 0 },
                         maxSize_ { 0 },

                         cursorVisible_ { true },
                         multilineEnabled_ { false },
                         focused_ { false },
                         hScroll_ { false },
                         vScroll_ { false }
{
    updateCursorSize();
}

void mp::TextBox::update(sf::Vector2i mousePosition)
{
    if (!isEnabled())
        return;

    setMousePosition(sf::Vector2f(mousePosition));

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        click();

    if (focused_)
    {
        setCurrentTexture(std::const_pointer_cast<const sf::Texture>(textureFocus_));
    }
    else if (mouseOnWidget())
    {
        setCurrentTexture(std::const_pointer_cast<const sf::Texture>(textureHover_));
    }
    else
    {
        setCurrentTexture(std::const_pointer_cast<const sf::Texture>(textureNormal_)); // Segmentation error, paske pas de texture chargée ?
    }
}

void mp::TextBox::click()
{
    if (mouseOnWidget())
    {
        focused_ = true;
    }
    else
    {
        focused_ = false;
    }
}

void mp::TextBox::setNormalTexture(const std::shared_ptr<sf::Texture> &texture)
{
    textureNormal_ = texture;
}

void mp::TextBox::setHoverTexture(const std::shared_ptr<sf::Texture> &texture)
{
    textureHover_ = texture;
}

void mp::TextBox::setFocusTexture(const std::shared_ptr<sf::Texture> &texture)
{
    textureFocus_ = texture;
}

void mp::TextBox::setFont(const sf::Font& font)
{
    text_.setFont(font);
}

void mp::TextBox::setCharacterSize(const unsigned int size)
{
    text_.setCharacterSize(size);
    updateCursorSize();
}

void mp::TextBox::setTextPos(const float& x, const float& y)
{
    text_.setPosition(x, y);
}

void mp::TextBox::setTextPos(const sf::Vector2f& position)
{
    text_.setPosition(position);
}

void mp::TextBox::setCursorPos(const size_t& pos)
{
    cursorPos_ = pos;
}

void mp::TextBox::hideCursor()
{
    cursor_.setVisible(false);
}

void mp::TextBox::showCursor()
{
    cursor_.setVisible(true);
}

void mp::TextBox::toggleCursor()
{
    if (cursor_.getVisible())
    {
        cursor_.setVisible(false);
    }
    else
    {
        cursor_.setVisible(true);
    }
}

void mp::TextBox::setCursorSize(const sf::Vector2f& size)
{
    cursor_.setSize(size);
}

void mp::TextBox::setCursorColor(const sf::Color& color)
{
    cursor_.setColor(color);
}

void mp::TextBox::enableMultiline()
{
    multilineEnabled_ = true;
}

void mp::TextBox::disableMultiline()
{
    multilineEnabled_ = false;
}

void mp::TextBox::focus()
{
    focused_ = true;
}

void mp::TextBox::unfocus()
{
    focused_ = false;
}

void mp::TextBox::setMaxSize(const size_t& size)
{
    maxSize_ = size;
}

void mp::TextBox::handleInput(const Uint32 &unicode)
{
    if (focused_)
    {
        switch (unicode)
        {
            case 13: // Enter
                if (multilineEnabled_)
                    addString(sf::String('\n'));
                break;
            case 8: // Backspace
                if (cursorPos_ > 0)
                    deleteText(cursorPos_ - 1, 1);
                break;
            case 127: // Delete
                deleteText(cursorPos_, 1);
                break;
            case 27: // Escape
                focused_ = false;
                break;
            default:
                if (!maxSize_ || text_.getString().getSize() < maxSize_)
                    addString(sf::String(unicode));
                break;
        }
    }
}

void mp::TextBox::setString(const sf::String& text)
{
    text_.setString(text);
    cursorPos_ = text.getSize();

    updateCursorPos();
}

void mp::TextBox::addString(const sf::String& text)
{
    insertText(cursorPos_, text);
}

void mp::TextBox::insertText(const size_t& position, const sf::String& text)
{
    sf::String newText { text_.getString() };
    newText.insert(position, text);
    text_.setString(newText);

    cursorPos_ = position + text.getSize();

    updateCursorPos();
}

void mp::TextBox::appendText(const sf::String& text)
{
    sf::String newText { text_.getString() };
    newText.insert(newText.getSize(), text);
    text_.setString(newText);

    cursorPos_ = newText.getSize();
}

void mp::TextBox::prependText(const sf::String& text)
{
    sf::String newText { text_.getString() };
    newText.insert(0, text);
    text_.setString(newText);

    cursorPos_ = text.getSize();

    updateCursorPos();
}

void mp::TextBox::deleteText(const size_t& pos, const size_t& n)
{
    sf::String newText { text_.getString() };
    newText.replace(pos, n, "");
    text_.setString(newText);

    cursorPos_ = pos;

    updateCursorPos();
}

unsigned int mp::TextBox::getCharacterSize() const
{
    return text_.getCharacterSize();
}

const size_t& mp::TextBox::getCursorPos() const
{
    return cursorPos_;
}

const bool& mp::TextBox::cursorIsVisible() const
{
    return cursor_.getVisible();
}

const sf::Vector2f& mp::TextBox::getCursorSize() const
{
    return cursor_.getSize();
}

const sf::Color& mp::TextBox::getCursorColor() const
{
    return cursor_.getColor();
}

const bool& mp::TextBox::multilineIsEnabled() const
{
    return multilineEnabled_;
}

const bool& mp::TextBox::isFocused() const
{
    return focused_;
}

const size_t& mp::TextBox::getMaxSize() const
{
    return maxSize_;
}

const sf::String& mp::TextBox::getString() const
{
    return text_.getString();
}

void mp::TextBox::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite_, states);
    target.draw(text_, states);
    target.draw(cursor_, states);
}

void mp::TextBox::updateCursorPos()
{
    cursor_.setPosition(text_.findCharacterPos(cursorPos_));
}

void mp::TextBox::updateCursorSize()
{
    cursor_.setSize({ 1, static_cast<float>(text_.getCharacterSize() + 2) });
}

