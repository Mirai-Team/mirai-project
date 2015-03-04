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

#ifndef MOUSEMANAGER_HPP_INCLUDED
#define MOUSEMANAGER_HPP_INCLUDED

#include <functional>
#include <map>
#include <string>

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>

#include "MiraiProject/inputManager/Binding.hpp"

/** @file MouseManager.hpp
 * \brief This file define MouseManager class.
 */

namespace mp
{
    /** \class MouseManager
     * \brief A class to handle mouse inputs.
     */
    
    class MouseManager
    {        
        public:
            /** \brief Constructor */
            MouseManager();

            /** \brief Destructor */
            ~MouseManager();

            /** \brief Add an action for a button.
             *
             * \param index : index of button in map.
             * \param buttons : a sfml button.
             * \param funct : function to launch when button is pressed or released.
             * \param mode : the mode for this binding (on release, on press, ...). See Binding::Mode enum.
             */
            void addBinding(std::string index, sf::Mouse::Button button, std::function<void()> funct = [](){ return true; }, mp::Binding::Mode mode = mp::Binding::Mode::Always);

            /** \brief Add an action for a button.
             *
             * \param index : index of button in map.
             * \param buttons : a vector of sfml buttons.
             * \param funct : function to launch when button is pressed or released.
             * \param mode : the mode for this binding (on release, on press, ...). See Binding::Mode enum.
             */
            void addBinding(std::string index, std::vector<sf::Mouse::Button> button, std::function<void()> funct = [](){ return true; }, mp::Binding::Mode mode = mp::Binding::Mode::Always);

            /** \brief Remove action.
             *
             * \param index : index of button in map.
             */
            void removeBinding(std::string index);

            /** \brief Clear all actions associated to a button. 
             *
             * \param button : the button matching bindings to remove.
             */
            void clearButton(sf::Mouse::Button button);

            /** \brief Clear all actions associated to buttons. 
             *
             * \param buttons : the buttons matching bindings to remove.
             */
            void clearButtons(std::vector<sf::Mouse::Button> buttons);

            /** \brief Execute action matching to the button. */
            void operator()();

            /** \brief disable the mouse manager */
            void disable();

            /** \brief enable the mouse manager */
            void enable();

            /** \brief Return whether the mouse manager is enabled or disabled
             *
             * \return a bool which contains the mouse manager state.
             */
            bool isEnabled() const;

        private:
            std::map<std::string, Binding> bindings_;

            bool enabled_;
    };
}

#endif // MOUSEMANAGER_HPP_INCLUDED