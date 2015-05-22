/* 
* @Author: Benoît CORTIER
* @Date:   2015-05-21 17:38:48
* @Last Modified by:   Benoît CORTIER
* @Last Modified time: 2015-05-21 19:07:31
*/

#include <iostream>

#include <MiraiProject/eventManager/EventManager.hpp>

#include "Entity.hpp"
#include "EventsTypes.hpp"

int Entity::lastId_ { 0 };

Entity::Entity() : id_    { lastId_ },
                   hp_    { 10 },
                   alive_ { true }
{
    mp::EventManager& eventManager = mp::EventManager::getInstance();

    ++lastId_; 

    std::cout << "Entity (" << id_ << ") created" << std::endl;

    eventManager.broadcast(ENTITY_CREATED, this);
}

void Entity::takeDamage(int damages)
{
    mp::EventManager& eventManager = mp::EventManager::getInstance();

    std::cout << "Entity (" << id_ << ") take " << damages << " damages." << std::endl;
    
    if (eventManager.broadcast(ENTITY_TAKE_DAMAGES, this, damages))
    {
        hp_ -= damages;
        if (hp_ <= 0)
            die();
    }
    else
    {
        std::cout << "(Ooops, in fact, it was canceled !)" << std::endl;
    }
}

void Entity::die()
{
    mp::EventManager& eventManager = mp::EventManager::getInstance();

    std::cout << "Entity (" << id_ << ") died." << std::endl;

    if (eventManager.broadcast(ENTITY_DIE, this))
    {
        hp_ = 0;
        alive_ = false;
    }
    else
    {
        std::cout << "(Ooops, in fact, it was canceled !)" << std::endl;
    }
}

bool Entity::isAlive() const
{
    return alive_;
}

int Entity::getId() const
{
    return id_;
}
