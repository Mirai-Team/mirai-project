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

namespace mp 
{
    template<>
    void EventManager::broadcast<void>(std::string eventName)
    {
        for(auto it = events_.begin(); it != events_.end(); ++it)
        {
            if(it->first == eventName)
                boost::any_cast<function<void()>>(events_[eventName])();
        }
    }
}