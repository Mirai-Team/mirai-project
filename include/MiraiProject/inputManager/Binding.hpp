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

#ifndef BINDING_HPP_INCLUDED
#define BINDING_HPP_INCLUDED

#include <functional>
#include <string>
#include <map>

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

/** @file Binding.hpp
 * \brief This file define Binding class.
 */

namespace mp
{
    /** \class Binding
     * \brief A class to bind keys and buttons to a given function.
     */
    
    class Binding
    {
        public:
            /** \brief Modes codes */
            enum Mode
            {
                Always = 0, ///< To call the function continuously.
                onRelease,  ///< To call the function only when releasing.
                onPress     ///< To call the function only on pressing.
            };

            /** \brief Constructor for keyboard keys.
             *
             * \param keys : the keys
             * \param funct : the function to call when the keys are pressed or released.
             * \param mode : the mode for this binding (on release, on press, ...). See Binding::Mode enum.
             */
            explicit Binding(std::vector<sf::Keyboard::Key> keys, std::function<void()> funct, Mode mode);

            /** \brief Constructor for mouse buttons.
             *
             * \param buttons : the buttons.
             * \param funct : the function to call when the buttons are pressed or released.
             * \param mode : the mode for this binding (on release, on press, ...). See Binding::Mode enum.
             */
            explicit Binding(std::vector<sf::Mouse::Button> buttons, std::function<void()> funct, Mode mode);

            /** \brief Destructor */
            ~Binding();

            /** \brief Call the binded function. */
            void callFunction();
            
            /** \brief Check whether the function should be called. 
             *
             * \return whether the function should be called
             */
            bool operator()();

            /** \brief Get the binded keys.
             *
             * \return the sfml keys.
             */
            std::vector<sf::Keyboard::Key> getKeys();

            /** \brief Get the binded buttons.
             *
             * \return the sfml buttons.
             */
            std::vector<sf::Mouse::Button> getButtons();

        private:
            bool isKeyboardBinding_;

            Mode mode_;

            std::vector<sf::Keyboard::Key> keys_;
            std::vector<bool> lastStateKeys_;

            std::vector<sf::Mouse::Button> buttons_;
            std::vector<bool> lastStateButtons_;

            std::function<void()> funct_;
    };
}

#endif // BINDING_HPP_INCLUDED