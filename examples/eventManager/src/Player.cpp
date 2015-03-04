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

#include <iostream>

#include "Player.hpp"

Player::Player() :  exp_ { 0 }
{
    function<void(int)> f = [=](int exp) {
        this->addExp(exp);
    };

    mp::EventManager& eventManager = mp::EventManager::getInstance();

    eventManager.addListener<void, int>("PlayerExp", f);
}

void Player::makeDamage(int damage, int monsterID)
{
    mp::EventManager& eventManager = mp::EventManager::getInstance();

    std::string eventName = "Monster" + mp::StringUtilities::toString(monsterID) + "isAlive";

    if (eventManager.broadcast<bool>(eventName))
    {
        eventName = "Monster" + mp::StringUtilities::toString(monsterID) + "TakeDamage";
        eventManager.broadcast<void, int>(eventName, damage);
    }
    else
        cout << "Monster" << monsterID << " is already dead or doesn't exist" << endl;
}

int Player::getExp()
{
    return exp_;
}

void Player::addExp(int exp)
{
    exp_ += exp;
}