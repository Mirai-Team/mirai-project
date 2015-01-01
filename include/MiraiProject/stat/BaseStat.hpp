////////////////////////////////////////////////////////////
//
// MiraiProject
// Copyright (C) 2014-2015 CORTIER Benoît (benoit.cortier@gmail.com), BOULMIER Jérôme (jerome.boulmier@outlook.com)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
// you must not claim that you wrote the original software.
// If you use this software in a product, an acknowledgment
// in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
// and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

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
