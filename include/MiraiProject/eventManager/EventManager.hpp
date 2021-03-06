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

#ifndef EVENTMANAGER_HPP_INCLUDED
#define EVENTMANAGER_HPP_INCLUDED

#include <functional>
#include <map>

#include <boost/any.hpp>

namespace mp
{
    class EventManager
    {
    public:
        /**
         * @brief Get an unique instance of EventManager.
         * @details If the manager doesn't exist, we create it and we return a reference of it.
         * @return An event manager reference.
         */
        static EventManager& getInstance();

        /**
         * @brief Add a Listener with parameter(s).
         *
         * @param eventID : Name of the event.
         * @param funct : Function to execute if Broadcast method is executed.
         * @tparam T : Function's type.
         * @tparam Args : Arguments' type.
         */
        template<typename... Args>
        void addListener(int eventID, int listenerID, std::function<bool(Args...)> funct);

        /**
         * @brief Delete a listener.
         *
         * @param eventID : Event ID matching the listener.
         * @param IDListener : Listener to delete.
         */
        void deleteListener(int eventID, int IDListener);

        /**
         * @brief Clear all listeners.
         */
        void clearListeners();

        /**
         * @brief Execute function register with AddListener
         *
         * @param eventID : Event to call.
         * @param args : Function's parameters.
         * @tparam T : Function's type.
         * @return If not void, return function return.
         */
        template<typename... Args>
        bool broadcast(int eventID, Args... args);

    private:
        EventManager();
        EventManager( const EventManager& other ) = delete;
        EventManager& operator=( const EventManager& ) = delete;

        std::map<int, std::vector<std::pair<int, boost::any>>> events_;
    };

}

#include "MiraiProject/eventManager/EventManager.tpp"

#endif
