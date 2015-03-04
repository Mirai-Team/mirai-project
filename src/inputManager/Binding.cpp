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

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <iostream>

#include "MiraiProject/inputManager/Binding.hpp"

mp::Binding::Binding(std::vector<sf::Keyboard::Key> keys, std::function<void()> funct, Mode mode) : isKeyboardBinding_{ true },
                                                                                                    mode_ { mode },
                                                                                                    keys_ { keys },
                                                                                                    lastStateKeys_ { false },
                                                                                                    buttons_ { },
                                                                                                    lastStateButtons_ { false },
                                                                                                    funct_ { funct }
{

}

mp::Binding::Binding(std::vector<sf::Mouse::Button> buttons, std::function<void()> funct, Mode mode) :  isKeyboardBinding_{ false },
                                                                                                        mode_ { mode },
                                                                                                        keys_ { },
                                                                                                        lastStateKeys_ { false },
                                                                                                        buttons_ { buttons },
                                                                                                        lastStateButtons_ { false },
                                                                                                        funct_ { funct }
{

}

mp::Binding::~Binding()
{

}

void mp::Binding::callFunction()
{
    if(funct_)
        funct_();
}

bool mp::Binding::operator()()
{
    bool IsPressed = true;

    for(unsigned int i = 0; i < keys_.size(); i++)
    {
        if(isKeyboardBinding_ and ((mode_ == Mode::Always and sf::Keyboard::isKeyPressed(keys_[i]))
           or (mode_ == Mode::onPress and lastStateKeys_[i] == false and sf::Keyboard::isKeyPressed(keys_[i]) == true)
           or (mode_ == Mode::onRelease and lastStateKeys_[i] == true and sf::Keyboard::isKeyPressed(keys_[i]) == false)))
            IsPressed &= true;
        else
            IsPressed = false;

        lastStateKeys_[i] = sf::Keyboard::isKeyPressed(keys_[i]);
    }

    for(unsigned int i = 0; i < buttons_.size(); i++)
    {
        if(!isKeyboardBinding_ and ((mode_ == Mode::Always and sf::Mouse::isButtonPressed(buttons_[i]))
           or (mode_ == Mode::onPress and lastStateButtons_[i] == false and sf::Mouse::isButtonPressed(buttons_[i]) == true)
           or (mode_ == Mode::onRelease and lastStateButtons_[i] == true and sf::Mouse::isButtonPressed(buttons_[i]) == false)))
            IsPressed &= true;
        else
            IsPressed = false;

        lastStateButtons_[i] = sf::Mouse::isButtonPressed(buttons_[i]);
    }

    return IsPressed;
}

std::vector<sf::Keyboard::Key> mp::Binding::getKeys()
{
    return keys_;
}

std::vector<sf::Mouse::Button> mp::Binding::getButtons()
{
    return buttons_;
}