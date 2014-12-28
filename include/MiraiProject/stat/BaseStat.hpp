#ifndef BASESTAT_HPP_INCLUDED
#define BASESTAT_HPP_INCLUDED

#include <vector>

namespace mp
{
	struct Buff {
		int value;
		bool isDebuff = 0;
	};
	
	class BaseStat {
		public:
			BaseStat();
            virtual ~BaseStat();
            
            int getBaseValue() const;
			void setBaseValue(int baseValue);
			
			int getBuffValue() const;
			void addBuffValue(Buff buff);
			void calculateBuffValue();
			
			int adjustedBaseValue() const;
		protected:    
			
		private:
			int baseValue_;
			int buffValue_;
			std::vector<Buff> buffs_;
			
	};
}

#endif // BASESTAT_HPP_INCLUDED
