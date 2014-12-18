#include <string>

#include <SFML/Graphics.hpp>

#include "util/WindowManager.hpp"

using namespace mp;

sf::RenderWindow WindowManager::window{ };
sf::View WindowManager::default_view{ };

bool WindowManager::fullscreen{ false };
bool WindowManager::vertical_sync{ false };
bool WindowManager::cursor_visible{ false };

int WindowManager::optimal_win_width{ 1024 };
int WindowManager::optimal_win_height{ 768 };

int WindowManager::videomode_width{ 1024 };
int WindowManager::videomode_height{ 768 };

std::string WindowManager::window_name{ "SFML Window" };


void WindowManager::create()
{
    // Creating the main window.
    if (fullscreen)
        window.create(sf::VideoMode(videomode_width, videomode_height, 32),
                      window_name,
                      sf::Style::Fullscreen);
    else
        window.create(sf::VideoMode(videomode_width, videomode_height, 32),
                      window_name,
                      sf::Style::Close | sf::Style::Titlebar);

    window.setMouseCursorVisible(cursor_visible); // Hide the cursor.
    window.setVerticalSyncEnabled(vertical_sync);

    // Setting up the class.
    setup();

    window.setView(default_view);
}

void WindowManager::setup()
{
    // _________ Setup default view _____________
    sf::Vector2u window_size{ window.getSize() };

    float win_ratio = static_cast<float>(window_size.x) / static_cast<float>(window_size.y);

    float left{ 0 };
    float top{ 0 };
    float width{ static_cast<float>(optimal_win_width) };
    float height{ static_cast<float>(optimal_win_height) };

    float idiff_width { static_cast<float>(window_size.x - optimal_win_width)
                        * (static_cast<float>(optimal_win_height) / static_cast<float>(optimal_win_width)) };
    float idiff_height { static_cast<float>(window_size.y - optimal_win_height)
                        * (static_cast<float>(optimal_win_width) / static_cast<float>(optimal_win_height)) };

    if (idiff_width > idiff_height)
    {
        // Width bigger... (by ratio)
        width = static_cast<float>(optimal_win_height) * win_ratio;
        left = (static_cast<float>(optimal_win_width) - static_cast<float>(width)) / 2;
    }
    else
    {
        // Height bigger... (by ratio)
        height = static_cast<float>(optimal_win_width) / win_ratio;
        top = (static_cast<float>(optimal_win_height) - static_cast<float>(height)) / 2;
    }

    sf::FloatRect rect{ left, top, width, height };
    default_view.reset(rect);
}

sf::RenderWindow& WindowManager::get_window()
{
    return window;
}

const sf::View& WindowManager::get_default_view()
{
    return default_view;
}


const bool& WindowManager::is_fullscreen()
{
	return fullscreen;
}

void WindowManager::set_fullscreen(const bool& value)
{
	fullscreen = value;
}

const bool& WindowManager::is_vertical_sync()
{
	return vertical_sync;
}

void WindowManager::set_vertical_sync(const bool& value)
{
	vertical_sync = value;
}

const bool& WindowManager::is_cursor_visible()
{
	return cursor_visible;
}

void WindowManager::set_cursor_visible(const bool& value)
{
	cursor_visible = value;
}


const int& WindowManager::get_optimal_win_width()
{
	return optimal_win_width;
}

void WindowManager::set_optimal_win_width(const int& value)
{
	optimal_win_width = value;
}

const int& WindowManager::get_optimal_win_height()
{
	return optimal_win_height;
}

void WindowManager::set_optimal_win_height(const int& value)
{
	optimal_win_height = value;
}


const int& WindowManager::get_videomode_width()
{
	return videomode_width;
}

void WindowManager::set_videomode_width(const int& value)
{
	videomode_width = value;
}

const int& WindowManager::get_videomode_height()
{
	return videomode_height;
}

void WindowManager::set_videomode_height(const int& value)
{
	videomode_height = value;
}


const std::string& WindowManager::get_window_name()
{
	return window_name;
}

void WindowManager::set_videomode_height(const std::string& value)
{
	window_name = value;
}
