#include "MiraiProject/eventManager/EventManager.hpp"

using namespace std;

mp::EventManager* mp::EventManager::instance_;

mp::EventManager* mp::EventManager::getInstance()
{
    if (!instance_)
        instance_ = new mp::EventManager();

    return instance_;
}

mp::EventManager::EventManager() : events_ { }
{

}
