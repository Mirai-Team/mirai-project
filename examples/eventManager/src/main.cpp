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
#include <functional>
#include <MiraiProject/eventManager/EventManager.hpp>

#include "EventsTypes.hpp"
#include "Entity.hpp"
#include "Monster.hpp"
#include "Player.hpp"

bool onEntityCreated(Entity* entityPtr)
{
    std::cout << "(I see a new entity (" << entityPtr->getId() << ").)" << std::endl;

    return true;
}

bool monster2Invincibility(Entity* ptrEntity, int /*damages*/)
{
    if (ptrEntity->getId() == 2)
    {
        return false;
    }

    return true;
}

int main()
{
    mp::EventManager& eventManager = mp::EventManager::getInstance();

    std::function<bool(Entity* entityPtr)> funct = [=](Entity* entityPtr) {
        return onEntityCreated(entityPtr);
    };

    std::function<bool(Entity* entityPtr, int damages)> funct2 = [=](Entity* entityPtr, int damages) {
        return monster2Invincibility(entityPtr, damages);
    };

    eventManager.addListener<Entity*>(ENTITY_CREATED, 0, funct);
    eventManager.addListener<Entity*>(ENTITY_TAKE_DAMAGES, 0, funct2);

    Player player;

    Monster monster1;
    Monster monster2;
    Monster monster3;
    Monster monster4;

    monster1.takeDamage(7);

    player.jump();

    monster1.takeDamage(7);
    monster2.takeDamage(10);

    player.jump();

    eventManager.clearListeners();

    return 0;
}
