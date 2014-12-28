#ifndef VITALSTAT_HPP_INCLUDED
#define VITALSTAT_HPP_INCLUDED

#include <vector>
#include <string>
#include "MiraiProject/stat/ModifiedStat.hpp"

namespace mp
{
	class VitalStat : public ModifiedStat {
		public:
			VitalStat();
			virtual ~VitalStat();
			
			/** \brief Get current value of stat.
			 * \return A int who contains the value.
			 *
			 */
			int getCurValue();
			
			/** \brief Set the current value of the stat.
			 * \param curValue : the value taken, max is adjustedBaseValue()
			 *
			 */
			void setCurValue(int curValue);
		private:
			int curValue_;
	};
}

#endif // VITALSTAT_HPP_INCLUDED
