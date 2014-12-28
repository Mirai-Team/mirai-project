#ifndef MODIFIEDSTAT_HPP_INCLUDED
#define MODIFIEDSTAT_HPP_INCLUDED

#include <vector>

#include "MiraiProject/stat/BaseStat.hpp"

namespace mp 
{
	struct ModifyingStat {
		BaseStat stat;
		float ratio;
	};
	
	class ModifiedStat : public BaseStat {
		
		public:
			ModifiedStat();
			virtual ~ModifiedStat();
			
			void AddModifier(ModifyingStat mod);
			void CalcultateModValue();
			int AdjustedBaseValue() const;
		protected:
		
		private:
			std::vector<ModifyingStat> _mods;
			int _modValue;
			
	};
}
#endif // MODIFIEDSTAT_HPP_INCLUDED
