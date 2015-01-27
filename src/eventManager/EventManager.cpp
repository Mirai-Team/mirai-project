#include "MiraiProject/eventManager/EventManager.hpp"

using namespace std;

mp::EventManager* mp::EventManager::instance_;

mp::EventManager* mp::EventManager::getInstance()
{
    if (!instance_)
        instance_ = new mp::EventManager();

    return instance_;
}

template<typename T, typename... Args>
void mp::EventManager::AddListener(std::string eventName, std::function<T(Args...)> funct)
{
    events_[eventName] = funct;
}

template<typename T, typename... Args>
T mp::EventManager::Broadcast(std::string eventName, Args... args)
{
    for(auto it = events_.begin(); it != events_.end(); ++it)
    {
        if(it->first == eventName)
            return boost::any_cast<function<T(Args...)>>(events_[eventName])(args...);
    }
}

template<typename T>
T mp::EventManager::Broadcast(std::string eventName)
{
    for(auto it = events_.begin(); it != events_.end(); ++it)
    {
        if(it->first == eventName)
            return boost::any_cast< function<T()> >(events_[eventName])();
    }
}

mp::EventManager::EventManager() : events_ { }
{

}
