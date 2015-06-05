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

#include "MiraiProject/inputManager/MouseManager.hpp"

mp::MouseManager::MouseManager() : bindings_ { },
                                   enabled_{ true }
{

}

mp::MouseManager::~MouseManager()
{

}

void mp::MouseManager::operator()()
{
    if (enabled_)
    {
        for(auto &binding : bindings_)
        {
            if(binding.second())
                binding.second.callFunction();
        }
    }
}

void mp::MouseManager::addBinding(std::string index, sf::Mouse::Button button, std::function<void()> funct, mp::Binding::Mode mode)
{
    std::vector<sf::Mouse::Button> temp;
    temp.push_back(button);

    bindings_.emplace(std::make_pair(index, mp::Binding(temp, funct, mode)));
}

void mp::MouseManager::addBinding(std::string index, std::vector<sf::Mouse::Button> buttons, std::function<void()> funct, mp::Binding::Mode mode)
{
    bindings_.emplace(std::make_pair(index, mp::Binding(buttons, funct, mode)));
}

void mp::MouseManager::removeBinding(std::string index)
{
    bindings_.erase(index);
}

void mp::MouseManager::clearButton(sf::Mouse::Button button)
{
    std::vector<sf::Mouse::Button> temp;
    temp.push_back(button);

    auto binding = bindings_.begin();
    while (binding != bindings_.end())
    {
        if (binding->second.getButtons() == temp)
            binding = bindings_.erase(binding);
        else
            binding++;
    }
}

void mp::MouseManager::clearButtons(std::vector<sf::Mouse::Button> buttons)
{
    auto binding = bindings_.begin();
    while (binding != bindings_.end())
    {
        if (binding->second.getButtons() == buttons)
            binding = bindings_.erase(binding);
        else
            binding++;
    }
}

void mp::MouseManager::enable()
{
    enabled_ = true;
}

void mp::MouseManager::disable()
{
    enabled_ = false;
}

bool mp::MouseManager::isEnabled() const
{
    return enabled_;
}
