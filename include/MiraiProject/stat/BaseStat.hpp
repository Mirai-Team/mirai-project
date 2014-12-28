#ifndef BASESTAT_HPP_INCLUDED
#define BASESTAT_HPP_INCLUDED

#include <vector>
#include <string>
#include <algorithm>

namespace mp
{
	struct Buff {
		int value;
		bool isDebuff = false;
		std::string name;
		
	};
	class BaseStat {
		public:
			BaseStat();
            virtual ~BaseStat();
            
            /** \brief Get base value of the stat.
			 * \return A int who contains the value.
			 *
			 */
            int getBaseValue() const;
            
            /** \brief Set the base value of the stat.
			 * \param baseValue : the value taken
			 *
			 */
			void setBaseValue(int baseValue);
			
			
			
			/** \brief Get buff value of the stat.
			 * \return A int who contains the value.
			 *
			 */
			int getBuffValue() const;
			
			/** \brief Add a Buff to the buff list
			 * \param buff : the buff
			 *
			 */
			void addBuff(Buff buff);
			
			/** \brief Delete a Buff to the buff list
			 * \param buff : the buff
			 *
			 */
			void deleteBuff(Buff buff);
			
			/** \brief Calculate the sum of each buff value
			 * If it's a buff, the value is add. 
			 * If it's a debuff, the value is substrate. 
			 *
			 */
			void calculateBuffValue();
			
			
			
			/** \brief Calculate max stat.
			 *  \return The buff value + the base value
			 */
			int adjustedBaseValue() const;
		protected:    
			
		private:
			int baseValue_;
			int buffValue_;
			std::vector<Buff> buffs_;
			
	};
}

#endif // BASESTAT_HPP_INCLUDED
