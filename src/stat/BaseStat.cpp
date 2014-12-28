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
