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

#ifndef MODIFIEDSTAT_HPP_INCLUDED
#define MODIFIEDSTAT_HPP_INCLUDED

#include <vector>

#include "MiraiProject/stat/BaseStat.hpp"

/** \file ModifiedStat.hpp
 * \brief This file contains ModifiedStat class and ModifyingStat structure definition.
 * ModifiedStat is for attributes like Strength, Spirit, etc...
 * In general for stats which don't need to be variables.
 */

namespace mp 
{
    /** \struct ModifyingStat
     * \brief Like Buff, but using ratio.
     */

    struct ModifyingStat 
    {
        /** \brief ratio : the stat on which depends the modified stat. */
        BaseStat stat; 

        /** \brief ratio : an augmentation or a diminution, between -1 and 1 */
        float ratio;
    };

    /** \class ModifiedStat
     * \brief Stat supporting ratio modification.
     */

    class ModifiedStat : public BaseStat 
    {
        public:
            /** \brief Constructor */
            ModifiedStat();

            /** \brief Destructor */
            virtual ~ModifiedStat();

            /** \brief Add a Modifier to the buff list.
             * 
             * \param buff : the buff.
             */
            void addModifier(ModifyingStat modifyingStat);

            /** \brief Calculate the sum of ratio*BaseValue */
            void calculateModValue();

            /** \brief Calculate max stat.
             * 
             * \return buff value + base value + mod value.
             */
            int adjustedBaseValue() const;

            /** \brief Get Base Stat.
             *
             * \return BaseStat object of the ModifiedStat class.
             */
            BaseStat GetBaseStat() const;

        private:
            std::vector<ModifyingStat> mods_;
            int modValue_;
    };
}
#endif // MODIFIEDSTAT_HPP_INCLUDED