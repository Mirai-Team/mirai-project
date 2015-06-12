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

#include "Entity.hpp"
#include "Player.hpp"
#include "EventsTypes.hpp"

Player::Player() :  xp_ { 0 }
{
    mp::EventManager& eventManager = mp::EventManager::getInstance();

    std::function<bool(Entity* entityPtr)> funct = [=](Entity* entityPtr) {
        return this->onEntityDie(entityPtr);
    };

    eventManager.addListener<Entity*>(ENTITY_DIE, getId(), funct);
}

Player::~Player()
{
    mp::EventManager& eventManager = mp::EventManager::getInstance();
    eventManager.deleteListener(ENTITY_DIE, getId());
}

void Player::jump()
{
    mp::EventManager& eventManager = mp::EventManager::getInstance();

    std::cout << "Player (" << getId() << ") jump." << std::endl;

    eventManager.broadcast(PLAYER_JUMP, this);
}

int Player::getXp() const
{
    return xp_;
}

void Player::giveXp(int xp)
{
    xp_ += xp;
}

bool Player::onEntityDie(Entity* /*entityPtr*/)
{
    giveXp(10);
    std::cout << "Player (" << getId() << ") gained 10 XP !" << std::endl;

    return true;
}
