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

#include "MiraiProject/inputManager/Binding.hpp"

mp::Binding::Binding(sf::Keyboard::Key key, bool onPress, std::function<void()> funct) : 	key_ { key },
																							button_ { },
																							onPress_ { onPress },
																							funct_ { funct }
{
	
}

mp::Binding::Binding(sf::Mouse::Button button, bool onPress, std::function<void()> funct) : 	key_ { },
																								button_ { button },
																								onPress_ { onPress },
																								funct_ { funct }
{
	
}
bool  mp::Binding::callFunction()
{
	if(funct_)
	{
		funct_();
		return true;
	}
	else
		return false;
	
}

bool mp::Binding::operator ()(sf::Event& event)
{
	if(event.key.code == key_)
		return((onPress_ && event.type == sf::Event::KeyPressed) || ((event.type == sf::Event::KeyReleased && !onPress_)));
	else
		return false;
}

sf::Keyboard::Key mp::Binding::getKey()
{
		return key_;
}

sf::Mouse::Button mp::Binding::getButton()
{
		return button_;
}
