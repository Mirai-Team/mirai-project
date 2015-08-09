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

#include <cmath>

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Font.hpp>

#include "MiraiProject/gui/TextBox.hpp"
#include "MiraiProject/gui/ClickableWidget.hpp"

namespace
{
    float manathan(sf::Vector2f a, sf::Vector2f b)
    {
        return static_cast<float>(fabs(a.x - b.x) + fabs(a.y - b.y));
    }
}

mp::TextBox::TextBox(float maxWidth, float maxHeight)
    : cursorVisible_{ true }
    , multilineEnabled_{ false }
    , focused_{ false }
    , hScroll_{ false }
    , vScroll_{ false }

    , nFirstVisible_{ 0 }
    , cursorPos_{ 0 }
    , maxSize_{ 0 }

    , textureNormal_{ }
    , textureHover_{ }
    , textureFocus_{ }

    , m_maxWidth{ maxWidth }
    , m_maxHeight{ maxHeight }

    , text_{ }
    , cursor_{ }
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

        // Move cursor at mouse's position.
        if (text_.getString().getSize())
        {
            size_t nearestChar = 0;
            sf::Vector2f globalPos = getWorldPosition();
            globalPos.y += static_cast<float>(text_.getCharacterSize() / 2);
            float bestDistance = manathan(text_.findCharacterPos(nearestChar) + globalPos, getMousePosition());
            for (size_t i = text_.getString().getSize(); --i; )
            {
                float distance = manathan(text_.findCharacterPos(i) + globalPos, getMousePosition());
                if (distance < bestDistance)
                {
                    bestDistance = distance;
                    nearestChar = i;
                }
            }

            if (bestDistance > text_.getCharacterSize())
                nearestChar = text_.getString().getSize();

            cursorPos_ = nearestChar;
            updateCursorPos();
        }
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
    updateCursorPos();
}

void mp::TextBox::setTextPos(const float& x, const float& y)
{
    text_.setPosition(x, y);
    updateCursorPos();
}

void mp::TextBox::setTextPos(const sf::Vector2f& position)
{
    text_.setPosition(position);
    updateCursorPos();
}

void mp::TextBox::setCursorPos(const size_t& pos)
{
    cursorPos_ = pos;
    updateCursorPos();
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

void mp::TextBox::setCursorColor(const sf::Color& color)
{
    cursor_.setColor(color);
}

void mp::TextBox::moveCursor(Direction direction)
{
    switch (direction)
    {
        case LEFT:
            if (cursorPos_)
            {
                --cursorPos_;
                updateCursorPos();
            }
            break;
        case RIGHT:
            if (cursorPos_ < text_.getString().getSize())
            {
                ++cursorPos_;
                updateCursorPos();
            }
            break;
        case UP:
        {
            size_t i{ 0 }, j{ 0 };

            while (cursorPos_ and text_.getString()[cursorPos_ - 1] != '\n')
            {
                ++i;
                --cursorPos_;
            }

            if (cursorPos_)
            {
                --cursorPos_;
                while (cursorPos_ and text_.getString()[cursorPos_ - 1] != '\n')
                {
                    ++j;
                    --cursorPos_;
                }

                if (j < i)
                {
                    cursorPos_ += j;
                }
                else
                {
                    cursorPos_ += i;
                }
            }

            updateCursorPos();
            break;
        }
        case DOWN:
        {
            size_t i{ 0 }, j{ 0 }, strSize{ text_.getString().getSize() };

            while (cursorPos_ and text_.getString()[cursorPos_ - 1] != '\n')
            {
                ++i;
                --cursorPos_;
            }

            while (cursorPos_ != strSize and text_.getString()[cursorPos_] != '\n')
                ++cursorPos_;

            if (cursorPos_ != strSize)
            {
                ++cursorPos_;
                while (cursorPos_ != strSize and j != i and text_.getString()[cursorPos_] != '\n')
                {
                    ++j;
                    ++cursorPos_;
                }
            }

            updateCursorPos();
            break;
        }
        case START:
            cursorPos_ = 0;
            updateCursorPos();
            break;
        case END:
            cursorPos_ = text_.getString().getSize();
            updateCursorPos();
            break;
        case STARTL: // Move to the beggining of the line.
            while (cursorPos_ and text_.getString()[cursorPos_-1] != '\n')
                --cursorPos_;
            updateCursorPos();
            break;
        case ENDL: // Move to the end of the line.
        {
            size_t strSize{ text_.getString().getSize() };
            while (cursorPos_ != strSize and text_.getString()[cursorPos_] != '\n')
                ++cursorPos_;
            updateCursorPos();
            break;
        }
        default:
            break;
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

void mp::TextBox::handleInput(const sf::Event &event)
{
    if (focused_)
    {
        switch (event.type)
        {
            case sf::Event::TextEntered:
                switch (event.text.unicode)
                {
                    case 13: // Enter
                        if (multilineEnabled_)
                        {
                            if (m_maxHeight > 1)
                            {
                                size_t strSize{ text_.getString().getSize() };
                                float yMax{ m_maxHeight - static_cast<float>(text_.getCharacterSize() * 2) };
                                if (text_.findCharacterPos(strSize).y < yMax)
                                    addString(sf::String('\n'));
                            }
                            else
                            {
                                addString(sf::String('\n'));
                            }
                        }
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
                        {
                            if (m_maxWidth > 1)
                            {
                                size_t i{ cursorPos_ }, strSize{ text_.getString().getSize() };
                                float xMax{ m_maxWidth - static_cast<float>(text_.getCharacterSize()) };

                                while (i != strSize and text_.getString()[i] != '\n')
                                    ++i;

                                if (text_.findCharacterPos(i).x < xMax)
                                    addString(sf::String(event.text.unicode));
                            }
                            else
                            {
                                addString(sf::String(event.text.unicode));
                            }
                        }
                        break;
                }
                break;
            case sf::Event::KeyPressed:
                switch (event.key.code)
                {
                    case sf::Keyboard::Key::Left:
                        moveCursor(LEFT);
                        break;
                    case sf::Keyboard::Key::Right:
                        moveCursor(RIGHT);
                        break;
                    case sf::Keyboard::Key::Up:
                        moveCursor(UP);
                        break;
                    case sf::Keyboard::Key::Down:
                        moveCursor(DOWN);
                        break;
                    case sf::Keyboard::Key::End:
                        moveCursor(ENDL);
                        break;
                    case sf::Keyboard::Key::Home:
                        moveCursor(STARTL);
                        break;
                    case sf::Keyboard::Key::PageDown:
                        moveCursor(END);
                        break;
                    case sf::Keyboard::Key::PageUp:
                        moveCursor(START);
                        break;
                    default:
                        break;
                }
                break;
            default:
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

void mp::TextBox::setMaxWidth(const float& width)
{
    m_maxWidth = width;
}

void mp::TextBox::setMaxHeight(const float& height)
{
    m_maxHeight = height;
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

const float& mp::TextBox::getMaxWidth() const
{
    return m_maxWidth;
}

const float& mp::TextBox::getMaxHeight() const
{
    return m_maxHeight;
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

