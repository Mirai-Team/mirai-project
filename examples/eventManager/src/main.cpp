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

#include "Monster.hpp"
#include "Player.hpp"

using namespace std;

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

    // We attempt to make damage to the first monster but he is already dead.
    player.makeDamage(5, 0);
    return 0;
}