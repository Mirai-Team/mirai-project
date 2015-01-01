#ifndef VITALSTAT_HPP_INCLUDED
#define VITALSTAT_HPP_INCLUDED

#include <vector>
#include <string>
#include "MiraiProject/stat/ModifiedStat.hpp"

/** \file VitalStat.hpp
 * \brief This file contains VitalStat class definition.
 */

namespace mp
{
	class VitalStat : public ModifiedStat {
		public:
			VitalStat();
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
