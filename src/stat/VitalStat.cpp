#include <vector>

#include "MiraiProject/stat/ModifiedStat.hpp"
#include "MiraiProject/stat/VitalStat.hpp"

mp::VitalStat::VitalStat() : 	ModifiedStat(),
								curValue_ { 0 }
									
{
	// constructor
}

mp::VitalStat::~VitalStat()
{
    // destructor
}

int mp::VitalStat::getCurValue()
{
	if(curValue_ > ModifiedStat().adjustedBaseValue())
		curValue_ = ModifiedStat().adjustedBaseValue();
		
	return curValue_;
}

void mp::VitalStat::setCurValue(int curValue)
{
	if(curValue > ModifiedStat().adjustedBaseValue())
		curValue = ModifiedStat().adjustedBaseValue();
		
	curValue_ = curValue;
}
