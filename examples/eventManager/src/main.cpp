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
#include <MiraiProject/util/StringUtilities.hpp>

#include "Monster.hpp"

using namespace std;

class Player
{
public:
    Player() : exp_ { 0 }
    {
        function<void(int)> f = [=](int exp) {
            return this->addExp(exp);
        };

        shared_ptr<mp::EventManager> eventManager = mp::EventManager::getInstance();

        eventManager->addListener<void, int>("PlayerExp", f);
    }

    void makeDamage(int damage, int monsterID)
    {
        std::string eventName = "Monster" + mp::StringUtilities::toString(monsterID) + "TakeDamage";

        shared_ptr<mp::EventManager> eventManager = mp::EventManager::getInstance();
        eventManager->broadcast<void, int>(eventName, damage);
    }

    int getExp()
    {
        return exp_;
    }

private:
    void addExp(int exp){
        exp_ += exp;
    }

    int exp_;
};

int main()
{
    Player player;

    // Monster0 doesn't exist so this line do nothing.
    player.makeDamage(10, 0);

    // We create two monsters.
    Monster monster0;
    Monster monster1;

    // We kill the first monster
    player.makeDamage(10, 0);

    cout << "Player exp = " << player.getExp() << endl;

    // We make 5 damages to the second monster.
    player.makeDamage(5, 1);
    monster1.setInvincibility(true);

    // We attempt to make damage to the second monster but he is invincible.
    player.makeDamage(5, 1);

    monster1.setInvincibility(false);

    // We make 5 damages to the second monster and so we kill him.
    player.makeDamage(5, 1);
    return 0;
}