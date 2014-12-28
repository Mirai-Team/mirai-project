#ifndef MODIFIEDSTAT_HPP_INCLUDED
#define MODIFIEDSTAT_HPP_INCLUDED

#include <vector>

#include "MiraiProject/stat/BaseStat.hpp"

namespace mp 
{
	struct ModifyingStat {
		/** \brief The stat of which depends the modified stat. 
		 * 
		 */
		BaseStat stat; 
		
		/** \brief An augmentation or a diminution
		 * By Exemple : 0.1 is an augmentation of 10%
		 * -0.1 is a diminution of 10%
		 * 
		 */
		float ratio;
	};
	
	class ModifiedStat : public BaseStat {
		
		public:
			ModifiedStat();
			virtual ~ModifiedStat();
			
			/** \brief Add a Modifier to the buff list
			 * \param buff : the buff
			 *
			 */
			void addModifier(ModifyingStat modifyingStat);
			
			/** \brief Calculate the sum of ratio*BaseValue
			 *
			 */
			void calculateModValue();
			
			/** \brief Calculate max stat.
			 * \return buff value + base value + mod value.
			 *
			 */
			int adjustedBaseValue() const;
			
			/** \brief Get Base Stat
			 *  \return BaseStat object of the ModifiedStat class.
			 */
			BaseStat GetBaseStat() const;
		protected:
		
		private:
			std::vector<ModifyingStat> mods_;
			int modValue_;
			
	};
}
#endif // MODIFIEDSTAT_HPP_INCLUDED
