#include "MiraiProject/eventManager/EventManager.hpp"

using namespace std;

mp::EventManager& mp::EventManager::getInstance()
{
    static mp::EventManager instance;
    return instance;
}

mp::EventManager::EventManager() : events_ { }
{

}

void mp::EventManager::deleteListener(std::string eventName)
{
    events_.erase(eventName);
}

void mp::EventManager::clearListeners()
{
    while(events_.size() > 0)
        events_.erase(events_.begin());
}