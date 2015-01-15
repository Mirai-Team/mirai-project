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

#ifndef VITALSTAT_HPP_INCLUDED
#define VITALSTAT_HPP_INCLUDED

#include <vector>
#include <string>
#include "MiraiProject/stat/ModifiedStat.hpp"

/** \file VitalStat.hpp
 * \brief This file contains VitalStat class definition.
 *  	VitalStat is for Stats like Mana, Energy, Life...
 *  	In General, for stats which need a variable value.
 */

namespace mp
{
	/** \class VitalStat
	 * \brief Stat with variable value.
	 */
	
	class VitalStat : public ModifiedStat 
	{
		public:
			/** \brief Constructor */
			VitalStat();
			
			/** \brief Destructor */
			virtual ~VitalStat();
			
			/** \brief Get current stat value.
			 * 
			 * \return an int which contains the value.
			 */
			int getCurValue();
			
			/** \brief Set the current stat value.
			 * 
			 * \param curValue : the new value, max is adjustedBaseValue()
			 */
			void setCurValue(int curValue);
			
		private:
			int curValue_;
	};
}

#endif // VITALSTAT_HPP_INCLUDED
