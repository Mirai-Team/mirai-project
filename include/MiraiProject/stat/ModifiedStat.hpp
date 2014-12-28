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
			
			void addModifier(ModifyingStat modifyingStat);
			void calculateModValue();
			int adjustedBaseValue() const;
		protected:
		
		private:
			std::vector<ModifyingStat> mods_;
			int modValue_;
			
	};
}
#endif // MODIFIEDSTAT_HPP_INCLUDED
