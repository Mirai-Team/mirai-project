#include "MiraiProject/stat/BaseStat.hpp"

using namespace std;

int mp::BaseStat::GetBaseValue() const
{
	return _baseValue;
}

void mp::BaseStat::SetBaseValue(int value)
{
	_baseValue = value;
}

int mp::BaseStat::GetBuffValue() const
{
	return _buffValue;
}

void mp::BaseStat::SetBuffValue(int value)
{
	_buffValue += value;
}

int mp::BaseStat::AdjustedBaseValue() const
{
	return _buffValue + _baseValue;
}
