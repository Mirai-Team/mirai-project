#include <vector>

#include "MiraiProject/stat/BaseStat.hpp"

using namespace std;

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

void mp::BaseStat::addBuffValue(mp::Buff buff)
{
	buffs_.push_back(buff);
}

void mp::BaseStat::calculateBuffValue()
{
	for(unsigned int i = 0; i<buffs_.size(); i++)
		if(buffs_[i].isDebuff)
			buffValue_ -= buffs_[i].value;
		else
			buffValue_ += buffs_[i].value;
}

int mp::BaseStat::adjustedBaseValue() const
{
	return buffValue_ + baseValue_;
}
