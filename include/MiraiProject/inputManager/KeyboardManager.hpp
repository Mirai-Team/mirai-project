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

#ifndef KEYBOARDMANAGER_HPP_INCLUDED
#define KEYBOARDMANAGER_HPP_INCLUDED

#include <functional>
#include <map>
#include <string>

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "MiraiProject/inputManager/Binding.hpp"

namespace mp
{	
	class KeyboardManager
	{
		
		public:
			
			/** \brief Constructor
			 */
			KeyboardManager();
			
			/** \brief Destructor
			 * 
			 */
			~KeyboardManager();
			
			/** \brief Add an action for a key.
			 * \param index : index of key in map.
			 * \param funct : function to launch when key is pressed or released.
			 * \param onPress : launch function when key is pressed or released.
			 */
			void addBinding(std::string index, sf::Keyboard::Key key, std::function<void()> funct = [](){return true;}, bool onPress = false);
			
			/** \brief Remove action.
			 * \param index : index of key in map.
			 */ 
			void removeBinding(std::string index);
			
			/** \brief Clear all actions associate to a key. 
			 * \param key : key to clean.
			 */
			void clearKey(sf::Keyboard::Key key);
			
			/** \brief Execute action relative to key.
			 * 
			 */
			bool operator()(sf::Event& event);
			
		private:
		
			std::map<std::string, Binding> bindings_;
	};
}

#endif // KEYBOARDMANAGER_HPP_INCLUDED
