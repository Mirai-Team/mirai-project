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

#ifndef BINDING_HPP_INCLUDED
#define BINDING_HPP_INCLUDED

#include <functional>
#include <string>
#include <map>

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

namespace mp
{
	class Binding
	{
		public:
			/** \brief Constructor for KeyboardManager
			 * \param key : a key
			 * \param funct : a function to launch when key is pressed or released.
			 */
			explicit Binding(sf::Keyboard::Key key, std::function<void()> funct);
			
			/** \brief Constructor for MouseManager
			 * \param button : a key
			 * \param funct : a function to launch when key is pressed or released.
			 */
			explicit Binding(sf::Mouse::Button button, std::function<void()> funct);
			
			/** \brief Destructor */
			~Binding();
			
			/** \brief Call function in funct_ */
			void callFunction();
			
			/** \brief Test if key is pressed or released. */
			bool operator()();
			
			/** \brief Key getter
			 *
			 * \return a sfml key.
			 */
			sf::Keyboard::Key getKey();
			
			/** \brief Button getter
			 *
			 * \return a sfml button.
			 */
			sf::Mouse::Button getButton();
			
		private:
			bool isKeyboardBinding;
		
			sf::Keyboard::Key key_;
			sf::Mouse::Button button_;
			
			std::function<void()> funct_;
	};
}

#endif // BINDING_HPP_INCLUDED
