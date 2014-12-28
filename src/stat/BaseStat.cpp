#include "MiraiProject/stat/BaseStat.hpp"

using namespace std;

mp::BaseStat::BaseStat() : baseValue_{ },
						   buffValue_{ }
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

void mp::BaseStat::addBuffValue(int buffValue)
{
	buffValue_ += buffValue;
}

int mp::BaseStat::adjustedBaseValue() const
{
	return buffValue_ + baseValue_;
}
