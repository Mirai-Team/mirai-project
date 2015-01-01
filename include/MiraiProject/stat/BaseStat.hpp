#ifndef BASESTAT_HPP_INCLUDED
#define BASESTAT_HPP_INCLUDED

#include <vector>
#include <string>
#include <algorithm>

/** \file BaseStat.hpp
 * \brief This file contains BaseStat class and Buff structure definition.
 */

namespace mp
{
	struct Buff 
	{
		int value = 0;
		bool isDebuff = false;
		std::string name = "unknown";
		
	};
	
	/** \class BaseStat
	 *
	 */
	
	class BaseStat 
	{
		public:
			BaseStat();
            virtual ~BaseStat();
            
            /** \brief Get the stat base value.
			 *
			 * \return an int which contains the value.
			 */
            int getBaseValue() const;
            
            /** \brief Set the stat base value.
			 * 
			 * \param baseValue : the value taken
			 */
			void setBaseValue(int baseValue);
			
			
			
			/** \brief Get the stat buff value.
			 * 
			 * \return an int which contains the value.
			 */
			int getBuffValue() const;
			
			/** \brief Add a Buff to the buff list.
			 * 
			 * \param buff : the buff.
			 */
			void addBuff(Buff buff);
			
			/** \brief Delete a buff from buff list.
			 * 
			 * \param buff : the buff.
			 */
			void deleteBuff(Buff buff);
			
			/** \brief Calculate the sum of each buff value.
			 *
			 * If it's a buff, the value is add. 
			 * If it's a debuff, the value is substrate. 
			 */
			void calculateBuffValue();
			
			
			
			/** \brief Calculate max stat.
			 *
			 * \return the buff value plus the base value.
			 */
			int adjustedBaseValue() const; 
			
		private:
			int baseValue_;
			int buffValue_;
			std::vector<Buff> buffs_;
			
	};
}

#endif // BASESTAT_HPP_INCLUDED
