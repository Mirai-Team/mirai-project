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

                         label_ { },

                         nFirstVisible_ { 0 },
                         cursorPos_ { 0 },
                         maxSize_ { 0 },

                         cursorVisible_ { true },
                         multilineEnabled_ { false },
                         focused_ { false },
                         hScroll_ { false },
                         vScroll_ { false }
{

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
    label_.setFont(font);
}

void mp::TextBox::setLabelPos(const float& x, const float& y)
{
    label_.setPosition(x, y);
}

void mp::TextBox::setLabelPos(const sf::Vector2f& position)
{
    label_.setPosition(position);
}

void mp::TextBox::setCursorPos(const size_t& pos)
{
    cursorPos_ = pos;
}

void mp::TextBox::hideCursor()
{
    cursorVisible_ = false;
}

void mp::TextBox::showCursor()
{
    cursorVisible_ = true;
}

void mp::TextBox::toggleCursor()
{
    if (cursorVisible_)
    {
        cursorVisible_ = false;
    }
    else
    {
        cursorVisible_ = true;
    }
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
    focused_ = false;
}

void mp::TextBox::handleInput(const Uint32 &unicode)
{
    if (focused_)
    {
        if (unicode == 13) // Enter
        {
            addText(sf::String('\n'));
        }
        else if (unicode == 8) // Backspace
        {
            if (cursorPos_ > 0)
                deleteText(cursorPos_ - 1, 1);
        }
        else if (unicode == 127) // Delete
        {
            deleteText(cursorPos_, 1);
        }
        else if (unicode == 27) // Escape
        {
            deleteText(cursorPos_, 1);
        }
        else
        {
            addText(sf::String(unicode));
        }
    }
}

void mp::TextBox::setText(const sf::String& text)
{
    label_.setText(text);
    cursorPos_ = text.getSize();
}

void mp::TextBox::addText(const sf::String& text)
{
    insertText(cursorPos_, text);
}

void mp::TextBox::insertText(const size_t& position, const sf::String& text)
{
    sf::String newText { label_.getText() };
    newText.insert(position, text);
    label_.setText(newText);

    cursorPos_ = position + text.getSize();
}

void mp::TextBox::appendText(const sf::String& text)
{
    sf::String newText { label_.getText() };
    newText.insert(newText.getSize(), text);
    label_.setText(newText);

    cursorPos_ = newText.getSize();
}

void mp::TextBox::prependText(const sf::String& text)
{
    sf::String newText { label_.getText() };
    newText.insert(0, text);
    label_.setText(newText);

    cursorPos_ = text.getSize();
}

void mp::TextBox::deleteText(const size_t& pos, const size_t& n)
{
    sf::String newText { label_.getText() };
    newText.replace(pos, n, "");
    label_.setText(newText);

    cursorPos_ = pos;
}

sf::String mp::TextBox::getText() const
{
    return label_.getText();
}

size_t mp::TextBox::getCursorPos() const
{
    return cursorPos_;
}

bool mp::TextBox::cursorIsVisible() const
{
    return cursorVisible_;
}

bool mp::TextBox::multilineIsEnabled() const
{
    return multilineEnabled_;
}

bool mp::TextBox::isFocused() const
{
    return focused_;
}

void mp::TextBox::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite_, states);
    target.draw(label_, states);
}
