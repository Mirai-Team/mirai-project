#include <vector>

#include "MiraiProject/stat/ModifiedStat.hpp"
#include "MiraiProject/stat/BaseStat.hpp"

using namespace std;

mp::ModifiedStat::ModifiedStat() : 	BaseStat(),
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
