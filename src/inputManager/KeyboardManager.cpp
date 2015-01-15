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

mp::KeyboardManager::KeyboardManager() : bindings_ { }
{
	
}

mp::KeyboardManager::~KeyboardManager()
{
	
}

bool mp::KeyboardManager::operator()(sf::Event& event)
{
	for(auto &binding : bindings_)
	{
		if(binding.second(event))
			return binding.second.callFunction();
	}
				
	return false;
}

void mp::KeyboardManager::addBinding(std::string index, sf::Keyboard::Key key, std::function<void()> funct, bool onPress)
{
	bindings_.emplace(std::make_pair(index, mp::Binding(key, onPress, funct)));
}

void mp::KeyboardManager::removeBinding(std::string index)
{
	bindings_.erase(index);
}

void mp::KeyboardManager::clearKey(sf::Keyboard::Key key)
{
	for(auto &binding : bindings_)
	{
		if(binding.second.getKey() == key)
			bindings_.erase(binding.first);
	}
}
