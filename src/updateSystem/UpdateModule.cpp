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

#include <algorithm>
#include <string>
#include <map>
#include <utility>

#include "MiraiProject/updateSystem/UpdateModule.hpp"
#include "MiraiProject/updateSystem/Updatable.hpp"

std::map<std::string, std::list<mp::Updatable*>> mp::UpdateModule::updatableList_;

void mp::UpdateModule::update(sf::Time deltaTime, std::string key)
{
    for_each(updatableList_[key].begin(), updatableList_[key].end(), [&](mp::Updatable* p)
    {
        p->update(deltaTime);
    });
}

void mp::UpdateModule::addUpdater(mp::Updatable* updatable, std::string key)
{
    // If key exist we push updatable in list according to key.
    // Else we create a list and add it in map.
    if (updatableList_.find(key) != updatableList_.end())
    {
        updatableList_[key].push_back(updatable);
    }
    else
    {
        std::list<mp::Updatable*> temp;
        temp.push_back(updatable);
        updatableList_[key] = temp;
    }
}

void mp::UpdateModule::removeUpdater(Updatable* updatable)
{
    for(auto &updatableClass : updatableList_)
    {
        updatableClass.second.remove_if([updatable] (Updatable* p) {
            return p == updatable;
        });
    }
}