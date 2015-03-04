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

#include "Monster.hpp"

int Monster::lastId_ { 0 };

Monster::Monster() :    id_ { lastId_ },
                        alive_ { true }
{
    cout << "Monster" << id_ << " created" << endl;
    life_ = 10;
    lastId_++; 
    function<void(int)> f = [=](int damage) {
        this->takeDamage(damage);
    };
    mp::EventManager& eventManager = mp::EventManager::getInstance();
    std::string eventName = "Monster" + mp::StringUtilities::toString(id_) + "TakeDamage";
    eventManager.addListener<void, int>(eventName, f);

    function<bool()> funct = [=]() {
        return this->isAlive();
    };

    eventName = "Monster" + mp::StringUtilities::toString(id_) + "isAlive";
    eventManager.addListener<bool>(eventName, funct);
}

void Monster::takeDamage(int damage)
{
    cout << "Monster" << id_ << " take " << damage << " damages" << endl;
    life_ -= damage;
    if (life_ <= 0)
    {
        life_ = 0;
        onDead();
    }
}

void Monster::setInvincibility(bool state)
{
    if (state)
    {
        mp::EventManager& eventManager = mp::EventManager::getInstance();
        std::string eventName = "Monster" + mp::StringUtilities::toString(id_) + "TakeDamage";
        eventManager.deleteListener(eventName);
    }
    else
    {
        mp::EventManager& eventManager = mp::EventManager::getInstance();
        std::string eventName = "Monster" + mp::StringUtilities::toString(id_) + "TakeDamage";
        function<void(int)> f = [=](int damage) {
            this->takeDamage(damage);
        };

        eventManager.addListener(eventName, f);
    }
}

bool Monster::isAlive()
{
    return alive_;
}

void Monster::onDead()
{
    if (alive_)
    {
        cout << "Monster" << id_ << " is dead" << endl;

        mp::EventManager& eventManager = mp::EventManager::getInstance();

        eventManager.broadcast<void, int>("PlayerExp", 10);
    }

    alive_ = false;
}