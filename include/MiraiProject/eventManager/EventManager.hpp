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

#ifndef EVENTMANAGER_HPP_INCLUDED
#define EVENTMANAGER_HPP_INCLUDED

#include <iostream>
#include <memory>
#include <functional>
#include <map>
#include <string>

#include <boost/any.hpp>
#include <boost/variant.hpp>

namespace mp
{
    class EventManager
    {
    public:
        static EventManager* getInstance();

        template<typename T, typename... Args>
        void AddListener(std::string eventName, std::function<T(Args...)> funct);
        template<typename T>
        void AddListener(std::string eventName, std::function<void()> funct)
        {
            events_[eventName] = funct;
        }

        template<typename T, typename... Args>
        T Broadcast(std::string eventName, Args... args);

        template<typename T>
        T Broadcast(std::string eventName);
        
    private:
        EventManager();
        static EventManager *instance_;

        std::map<std::string, boost::any> events_;
    };
}

#endif
