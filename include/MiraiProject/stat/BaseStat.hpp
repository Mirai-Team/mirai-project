#ifndef BASESTAT_HPP_INCLUDED
#define BASESTAT_HPP_INCLUDED

namespace mp
{
	class BaseStat {
		public:
			BaseStat();
            virtual ~BaseStat();
            
            int GetBaseValue() const;
			void SetBaseValue(int value);
			
			int GetBuffValue() const;
			void AddBuffValue(int value);
			
			int AdjustedBaseValue() const;
		protected:    
			int _baseValue;
			int _buffValue;
		private:
			
			
	};
}

#endif // BASESTAT_HPP_INCLUDED
