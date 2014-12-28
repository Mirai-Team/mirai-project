#include <vector>

#include "MiraiProject/stat/ModifiedStat.hpp"
#include "MiraiProject/stat/BaseStat.hpp"

using namespace std;

mp::ModifiedStat::ModifiedStat() : 	BaseStat(),
									_mods { },
									_modValue { }
									
{
}	
void mp::ModifiedStat::AddModifier(mp::ModifyingStat mod)
{
	_mods.push_back(mod);
}

void mp::ModifiedStat::CalcultateModValue() {
	_modValue = 0; 
	
	for(unsigned int i = 0; i<_mods.size();i++)
		_modValue += static_cast<int>(static_cast<float>(_mods[i].stat.GetBaseValue()) * (1+_mods[i].ratio));
			
}

int mp::ModifiedStat::AdjustedBaseValue() const {
	return (_baseValue+ _buffValue + _modValue);
}
