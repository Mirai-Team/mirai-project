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

/** @file KeyboardManager.hpp
 * \brief This file define KeyboardManager class.
 */
 
namespace mp
{
    /** \class KeyboardManager
     * \brief A class to handle keyboard inputs.
     */
    
    class KeyboardManager
    {
        public:
            /** \brief Constructor */
            KeyboardManager();

            /** \brief Destructor */
            ~KeyboardManager();

            /** \brief Add an action for a key.
             *
             * \param index : index of key in map.
             * \param keys : a sfml key.
             * \param funct : function to launch when key is pressed or released.
             * \param mode : the mode for this binding (on release, on press, ...). See Binding::Mode enum.
             */
            void addBinding(std::string index, sf::Keyboard::Key key, std::function<void()> funct = [](){ return true; }, mp::Binding::Mode mode = mp::Binding::Mode::Always);

            /** \brief Add an action for a key.
             *
             * \param index : index of key in map.
             * \param keys : a vector of sfml keys.
             * \param funct : function to launch when key is pressed or released.
             * \param mode : the mode for this binding (on release, on press, ...). See Binding::Mode enum.
             */
            void addBinding(std::string index, std::vector<sf::Keyboard::Key> keys, std::function<void()> funct = [](){ return true; }, mp::Binding::Mode mode = mp::Binding::Mode::Always);

            /** \brief Remove action.
             *
             * \param index : index of key in map.
             */ 
            void removeBinding(std::string index);

            /** \brief Clear all actions associated to a key. 
             *
             * \param key : the key matching bindings to remove.
             */
            void clearKey(sf::Keyboard::Key key);

            /** \brief Clear all actions associated to keys. 
             *
             * \param keys : the keys matching bindings to remove.
             */
            void clearKeys(std::vector<sf::Keyboard::Key> keys);

            /** \brief Execute action matching to the key. */
            void operator()();

            /** \brief disable the keyboard manager */
            void disable();

            /** \brief enable the keyboard manager */
            void enable();

            /** \brief Return whether the keyboard manager is enabled or disabled
             *
             * \return a bool which contains the keyboard manager state.
             */
            bool isEnabled() const;

        private:
            std::map<std::string, Binding> bindings_;

            bool enabled_;
    };
}

#endif // KEYBOARDMANAGER_HPP_INCLUDED