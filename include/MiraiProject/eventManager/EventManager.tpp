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

#ifndef EVENT_MANAGER_TPP_INCLUDED
#define EVENT_MANAGER_TPP_INCLUDED

#include "MiraiProject/eventManager/EventManager.hpp"

using namespace std;

template<typename T, typename... Args>
void mp::EventManager::addListener(std::string eventName, std::function<T(Args...)> funct)
{
    events_[eventName] = funct;
}

template<typename T>
void mp::EventManager::addListener(std::string eventName, std::function<T()> funct)
{
    events_[eventName] = funct;
}

template<typename T, typename... Args>
T mp::EventManager::broadcast(std::string eventName, Args... args)
{
    for(auto it = events_.begin(); it != events_.end(); ++it)
    {
        if(it->first == eventName)
            return boost::any_cast<function<T(Args...)>>(events_[eventName])(args...);
    }
}

template<typename T>
T mp::EventManager::broadcast(std::string eventName)
{
    for(auto it = events_.begin(); it != events_.end(); ++it)
    {
        if(it->first == eventName)
            return boost::any_cast< function<T()> >(events_[eventName])();
    }
}

#endif // EVENT_MANAGER_TPP_INCLUDED