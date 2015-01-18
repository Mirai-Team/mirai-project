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

#include <vector>

#include "MiraiProject/stat/ModifiedStat.hpp"
#include "MiraiProject/stat/BaseStat.hpp"

using namespace std;

mp::ModifiedStat::ModifiedStat() :  BaseStat(),
                                    mods_ { },
                                    modValue_ { }
{
    // constructor
}

mp::ModifiedStat::~ModifiedStat()
{
    // destructor
}

void mp::ModifiedStat::addModifier(mp::ModifyingStat modifyingStat)
{
    mods_.push_back(modifyingStat);
}

void mp::ModifiedStat::calculateModValue() {
    modValue_ = 0;

    for(unsigned int i = 0; i<mods_.size(); i++)
        modValue_ += static_cast<int>(static_cast<float>( mods_[i].stat.getBaseValue() ) * mods_[i].ratio );

}

int mp::ModifiedStat::adjustedBaseValue() const {
    return ( getBaseValue() + getBuffValue() + modValue_ );
}

mp::BaseStat mp::ModifiedStat::GetBaseStat() const {
    return BaseStat();
}