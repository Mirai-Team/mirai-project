////////////////////////////////////////////////////////////
//
// MiraiProject
// Copyright (C) 2014-2015 CORTIER Benoît (benoit.cortier@gmail.com), BOULMIER Jérôme (jerome.boulmier@outlook.com)
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

using namespace std;

class Test
{
public:
    Test()
    {
        std::function<int(int)> f = [=](int a) {
            return this->displayDamage(a);
        };
        shared_ptr<mp::EventManager> eventManager = mp::EventManager::getInstance();
        eventManager->AddListener<int, int>("helloWorld", f);

    }

    int displayDamage(int a)
    {
        cout << "I took " << a << " damages points." << endl;

        if(a >= 10)
            return 0;
        else
            return 1;
    }
    
};

class Test2
{
public:

    void makeDamage(int damage)
    {
        shared_ptr<mp::EventManager> eventManager = mp::EventManager::getInstance();
        int state = eventManager->Broadcast<int, int>("helloWorld", damage);
        if(state == 0) {
            cout << "I'm Dead" << endl;
        }else
        {
            cout << "I'm alive" << endl;
        }
    }
    
};
int main()
{
    Test test;
    Test2 test2;

    test2.makeDamage(10);
    return 0;
}