#include <string>

#include <SFML/Graphics.hpp>

#include "MiraiProject/util/WindowManager.hpp"

using namespace mp;

sf::RenderWindow WindowManager::window_{ };
sf::View WindowManager::defaultView_{ };

bool WindowManager::fullscreen_{ false };
bool WindowManager::verticalSync_{ false };
bool WindowManager::cursorVisible_{ false };

int WindowManager::optimalWinWidth_{ 1024 };
int WindowManager::optimalWinHeight_{ 768 };

int WindowManager::videomodeWidth_{ 1024 };
int WindowManager::videomodeHeight_{ 768 };

std::string WindowManager::windowName_{ "SFML Window" };


void WindowManager::create()
{
    // Creating the main window.
    if (fullscreen_)
        window_.create(sf::VideoMode(videomodeWidth_, videomodeHeight_, 32),
                      windowName_,
                      sf::Style::Fullscreen);
    else
        window_.create(sf::VideoMode(videomodeWidth_, videomodeHeight_, 32),
                      windowName_,
                      sf::Style::Close | sf::Style::Titlebar);

    window_.setMouseCursorVisible(cursorVisible_); // Hide the cursor.
    window_.setVerticalSyncEnabled(verticalSync_);

    // Setting up the class.
    setup();

    window_.setView(defaultView_);
}

void WindowManager::setup()
{
    // _________ Setup default view _____________
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
}

sf::RenderWindow& WindowManager::getWindow()
{
    return window_;
}

const sf::View& WindowManager::getDefaultView()
{
    return defaultView_;
}


const bool& WindowManager::isFullscreen()
{
	return fullscreen_;
}

void WindowManager::setFullscreen(const bool& fullscreen)
{
	fullscreen_ = fullscreen;
}

const bool& WindowManager::isVerticalSync()
{
	return verticalSync_;
}

void WindowManager::setVerticalSync(const bool& verticalSync)
{
	verticalSync_ = verticalSync;
}

const bool& WindowManager::isCursorVisible()
{
	return cursorVisible_;
}

void WindowManager::setCursorVisible(const bool& cursorVisible)
{
	cursorVisible_ = cursorVisible;
}


const int& WindowManager::getOptimalWinWidth()
{
	return optimalWinWidth_;
}

void WindowManager::setOptimalWinWidth(const int& value)
{
	optimalWinWidth_ = value;
}

const int& WindowManager::getOptimalWinHeight()
{
	return optimalWinHeight_;
}

void WindowManager::setOptimalWinHeight(const int& value)
{
	optimalWinHeight_ = value;
}


const int& WindowManager::getVideomodeWidth()
{
	return videomodeWidth_;
}

void WindowManager::setVideomodeWidth(const int& videomodeWidth)
{
	videomodeWidth_ = videomodeWidth;
}

const int& WindowManager::getVideomodeHeight()
{
	return videomodeHeight_;
}

void WindowManager::setVideomodeHeight(const int& videomodeHeight)
{
	videomodeHeight_ = videomodeHeight;
}


const std::string& WindowManager::getWindowName()
{
	return windowName_;
}

void WindowManager::setVideomodeHeight(const std::string& windowName)
{
	windowName_ = windowName;
}
