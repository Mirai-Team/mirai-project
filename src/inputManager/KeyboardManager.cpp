////////////////////////////////////////////////////////////
//
// MiraiProject
// Copyright (C) 2014-2015 CORTIER Benoît (benoit.cortier@gmail.com), BOULMIER Jérôme (jerome.boulmier@outlook.com)
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

#include "MiraiProject/inputManager/KeyboardManager.hpp"

mp::KeyboardManager::KeyboardManager() : bindings_{ },
                                         enabled_{ true }
{

}

mp::KeyboardManager::~KeyboardManager()
{

}

void mp::KeyboardManager::operator()()
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

void mp::KeyboardManager::addBinding(std::string index, sf::Keyboard::Key key, std::function<void()> funct, mp::Binding::Mode mode)
{
    std::vector<sf::Keyboard::Key> temp;
    temp.push_back(key);

    bindings_.emplace(std::make_pair(index, mp::Binding(temp, funct, mode)));
}

void mp::KeyboardManager::addBinding(std::string index, std::vector<sf::Keyboard::Key> keys, std::function<void()> funct, mp::Binding::Mode mode)
{
    bindings_.emplace(std::make_pair(index, mp::Binding(keys, funct, mode)));
}

void mp::KeyboardManager::removeBinding(std::string index)
{
    bindings_.erase(index);
}

void mp::KeyboardManager::clearKey(sf::Keyboard::Key key)
{
    std::vector<sf::Keyboard::Key> temp;
    temp.push_back(key);

    auto binding = bindings_.begin();
    while (binding != bindings_.end())
    {
        if (binding->second.getKeys() == temp)
            binding = bindings_.erase(binding);
        else
            binding++;
    }
}

void mp::KeyboardManager::clearKey(std::vector<sf::Keyboard::Key> keys)
{
    auto binding = bindings_.begin();
    while (binding != bindings_.end())
    {
        if (binding->second.getKeys() == keys)
            binding = bindings_.erase(binding);
        else
            binding++;
    }
}

void mp::KeyboardManager::enable()
{
    enabled_ = true;
}

void mp::KeyboardManager::disable()
{
    enabled_ = false;
}

bool mp::KeyboardManager::isEnabled() const
{
    return enabled_;
}