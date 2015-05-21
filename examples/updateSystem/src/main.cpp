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

#include <SFML/System/Time.hpp>

using namespace std;

class SomeClass
{
    public:
        SomeClass()
        {
            mp::EventManager& eventManager = mp::EventManager::getInstance();

            std::function<bool(sf::Time)> updateFunct = [=](sf::Time deltaTime){
                return this->update(deltaTime);
            };

            eventManager.addListener(0, updateFunct);
        };
        //Since void mp::Updatable::Update() is virtual, it's necessary to create this function.
        bool update(sf::Time deltaTime)
        {
            std::cout << deltaTime.asSeconds() << std::endl;

            return true;
        }
};

int main()
{
    SomeClass * a = new SomeClass();
    SomeClass * b = new SomeClass();

    mp::EventManager::getInstance().broadcast<sf::Time>(0, sf::seconds(2.55486f));

    delete b;

    mp::EventManager::getInstance().broadcast<sf::Time>(0, sf::seconds(2.55486f));
    return 0;
}