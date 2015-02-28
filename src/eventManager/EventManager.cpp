#include "MiraiProject/eventManager/EventManager.hpp"

using namespace std;

shared_ptr<mp::EventManager> mp::EventManager::instance_;

shared_ptr<mp::EventManager> mp::EventManager::getInstance()
{
    if (!instance_)
        instance_ = make_shared<mp::EventManager>(mp::EventManager());

    return instance_;
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