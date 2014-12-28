#ifndef BASESTAT_HPP_INCLUDED
#define BASESTAT_HPP_INCLUDED

namespace mp
{
	class BaseStat {
		public:
			BaseStat();
            virtual ~BaseStat();
            
            int getBaseValue() const;
			void setBaseValue(int baseValue);
			
			int getBuffValue() const;
			void addBuffValue(int buffValue);
			
			int adjustedBaseValue() const;
		protected:    
			int baseValue_;
			int buffValue_;
		private:
			
			
	};
}

#endif // BASESTAT_HPP_INCLUDED
