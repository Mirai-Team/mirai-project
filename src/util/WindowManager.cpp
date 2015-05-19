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

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "MiraiProject/util/WindowManager.hpp"

using namespace mp;

WindowManager::WindowManager(const bool& fullscreen, const bool& verticalSync, const bool& cursorVisible,
                             const int& optimalWinWidth, const int& optimalWinHeight,
                             const int& videoModeWidth, const int& videoModeHeight,
                             const std::string& windowName, const sf::Color& bordersColor) :
            window_{ },
            defaultView_{ },

            fullscreen_{ fullscreen },
            verticalSync_{ verticalSync },
            cursorVisible_{ cursorVisible },

            optimalWinWidth_{ optimalWinWidth },
            optimalWinHeight_{ optimalWinHeight },

            videoModeWidth_{ videoModeWidth },
            videoModeHeight_{ videoModeHeight },

            windowName_{ windowName },
            
            borders_{ }
{
    sf::RectangleShape border{ };
    border.setFillColor(bordersColor);
    
    // Put two borders with wanted colour.
    for (unsigned int i = 0 ; i < 2 ; i++)
        borders_.push_back(border);
}

WindowManager::~WindowManager()
{
    // Destructor
}


void WindowManager::create()
{
    // Creating the main window.
    if (fullscreen_)
    {
        window_.create(sf::VideoMode(videoModeWidth_, videoModeHeight_, 32),
                      windowName_,
                      sf::Style::Fullscreen);
    }
    else
    {
        window_.create(sf::VideoMode(videoModeWidth_, videoModeHeight_, 32),
                      windowName_,
                      sf::Style::Close | sf::Style::Titlebar);
    }

    window_.setMouseCursorVisible(cursorVisible_); // Hide the cursor.
    window_.setVerticalSyncEnabled(verticalSync_);

    // Setting up the class.
    setup();

    window_.setView(defaultView_);
}

void WindowManager::setup()
{   
    // _________ Set up default view _____________
    sf::Vector2u window_size{ window_.getSize() };

    float win_ratio = static_cast<float>(window_size.x) / static_cast<float>(window_size.y);

    float left{ 0 };
    float top{ 0 };
    float width{ static_cast<float>(optimalWinWidth_) };
    float height{ static_cast<float>(optimalWinHeight_) };

    float idiff_width { static_cast<float>(window_size.x - optimalWinWidth_)
                        * (static_cast<float>(optimalWinHeight_) / static_cast<float>(optimalWinWidth_)) };
    float idiff_height { static_cast<float>(window_size.y - optimalWinHeight_)
                        * (static_cast<float>(optimalWinWidth_) / static_cast<float>(optimalWinHeight_)) };

    if (idiff_width > idiff_height)
    {
        // Width bigger... (by ratio)
        width = static_cast<float>(optimalWinHeight_) * win_ratio;
        left = (static_cast<float>(optimalWinWidth_) - static_cast<float>(width)) / 2;
    }
    else
    {
        // Height bigger... (by ratio)
        height = static_cast<float>(optimalWinWidth_) / win_ratio;
        top = (static_cast<float>(optimalWinHeight_) - static_cast<float>(height)) / 2;
    }

    sf::FloatRect rect{ left, top, width, height };
    defaultView_.reset(rect);
    
    // _________ Set up borders dimensions _____________
    sf::Vector2f bordersSize{ };
    
    if (idiff_width > idiff_height)
    {
        bordersSize.x = (width - static_cast<float>(optimalWinWidth_)) / 2;
        bordersSize.y = height;
        
        borders_[0].setPosition(-bordersSize.x, 0);
        borders_[1].setPosition(static_cast<float>(optimalWinWidth_), 0);
    }
    else
    {
        bordersSize.x = width;
        bordersSize.y = (height - static_cast<float>(optimalWinHeight_)) / 2;
        
        borders_[0].setPosition(0, -bordersSize.y);
        borders_[1].setPosition(0, static_cast<float>(optimalWinHeight_));
    }
    
    for (unsigned int i = 0 ; i < borders_.size() ; i++)
        borders_[i].setSize(bordersSize);
}

sf::RenderWindow& WindowManager::getWindow()
{
    return window_;
}

const sf::View& WindowManager::getDefaultView() const
{
    return defaultView_;
}


const bool& WindowManager::isFullscreen() const
{
    return fullscreen_;
}

void WindowManager::setFullscreen(const bool& fullscreen)
{
    fullscreen_ = fullscreen;
}

const bool& WindowManager::isVerticalSync() const
{
    return verticalSync_;
}

void WindowManager::setVerticalSync(const bool& verticalSync)
{
    verticalSync_ = verticalSync;
}

const bool& WindowManager::isCursorVisible() const
{
    return cursorVisible_;
}

void WindowManager::setCursorVisible(const bool& cursorVisible)
{
    cursorVisible_ = cursorVisible;
}


const int& WindowManager::getOptimalWinWidth() const
{
    return optimalWinWidth_;
}

void WindowManager::setOptimalWinWidth(const int& optimalWinWidth)
{
    optimalWinWidth_ = optimalWinWidth;
}

const int& WindowManager::getOptimalWinHeight() const
{
    return optimalWinHeight_;
}

void WindowManager::setOptimalWinHeight(const int& optimalWinHeight)
{
    optimalWinHeight_ = optimalWinHeight;
}


const int& WindowManager::getVideomodeWidth() const
{
    return videoModeWidth_;
}

void WindowManager::setVideomodeWidth(const int& videoModeWidth)
{
    videoModeWidth_ = videoModeWidth;
}

const int& WindowManager::getVideomodeHeight() const
{
    return videoModeHeight_;
}

void WindowManager::setVideomodeHeight(const int& videoModeHeight)
{
    videoModeHeight_ = videoModeHeight;
}


const std::string& WindowManager::getWindowName() const
{
    return windowName_;
}

void WindowManager::setWindowName(const std::string& windowName)
{
    windowName_ = windowName;
}


void WindowManager::setBordersColor(sf::Color newColor)
{
    for (unsigned int i = 0 ; i < borders_.size() ; i++)
        borders_[i].setFillColor(newColor);
}

void WindowManager::drawBorders()
{
    // Set the default view to draw borders.
    window_.setView(defaultView_);
    
    for (unsigned int i = 0 ; i < borders_.size() ; i++)
        window_.draw(borders_[i]);
}