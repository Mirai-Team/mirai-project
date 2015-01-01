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
#include <iostream>

#include "MiraiProject/stat/BaseStat.hpp"

using namespace std;

bool operator==(mp::Buff const& a, mp::Buff const& b)
{
		return (a.name == b.name && a.value == b.value && a.isDebuff == b.isDebuff);
}

mp::BaseStat::BaseStat() : baseValue_{ },
						   buffValue_{ },
						   buffs_ { }
{
	// constructor
}

mp::BaseStat::~BaseStat()
{
    // destructor
}

// Setters and Getters region
int mp::BaseStat::getBaseValue() const
{
	return baseValue_;
}

void mp::BaseStat::setBaseValue(int baseValue)
{
	baseValue_ = baseValue;
}

int mp::BaseStat::getBuffValue() const
{
	return buffValue_;
}

// end of region


void mp::BaseStat::addBuff(mp::Buff buff)
{
	buffs_.push_back(buff);
}

void mp::BaseStat::deleteBuff(mp::Buff buff)
{
	for(unsigned int i = 0; i < buffs_.size() ; i++)
	{
		
		if(buffs_[i] == buff)
			buffs_.erase(buffs_.begin()+i);
			
	}
}

void mp::BaseStat::calculateBuffValue()
{
	buffValue_ = 0;
	for(unsigned int i = 0; i<buffs_.size(); i++)
	{
		
		if(buffs_[i].isDebuff)
			buffValue_ -= buffs_[i].value;
		else
			buffValue_ += buffs_[i].value;
			
	}
}

int mp::BaseStat::adjustedBaseValue() const
{
	return buffValue_ + baseValue_;
}
