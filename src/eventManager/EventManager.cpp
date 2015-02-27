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
