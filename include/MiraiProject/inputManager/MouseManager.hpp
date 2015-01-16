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

#ifndef MOUSEMANAGER_HPP_INCLUDED
#define MOUSEMANAGER_HPP_INCLUDED

#include <functional>
#include <map>
#include <string>

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>

#include "MiraiProject/inputManager/Binding.hpp"

namespace mp
{	
	class MouseManager
	{
		public:
			MouseManager();
			~MouseManager();
			
			void addBinding(std::string index, sf::Mouse::Button button, std::function<void()> funct = [](){ return true; });
			void addBinding(std::string index, std::vector<sf::Mouse::Button> button, std::function<void()> funct = [](){ return true; });
			
			void removeBinding(std::string index);
			
			void clearButton(sf::Mouse::Button button);
			
			void clearButton(std::vector<sf::Mouse::Button> buttons);
			
			void operator()();
			
			void disable();
			
			void enable();
			
			bool isEnabled() const;
			
		private:
			std::map<std::string, Binding> bindings_;
			
			bool enabled_;
	};
}

#endif // MOUSEMANAGER_HPP_INCLUDED
