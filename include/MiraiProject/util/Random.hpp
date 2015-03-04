////////////////////////////////////////////////////////////
//
// MiraiProject
// Copyright (C) 2014-2015 CORTIER Benoît (benoit.cortier@gmail.com), BOULMIER Jérôme (jerome.boulmier@outlook.fr)
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

#ifndef RANDOM_HPP_INCLUDED
#define RANDOM_HPP_INCLUDED

#include <iostream>
#include <chrono>
#include <random>
#include <vector>

/** @file random.hpp
 * \brief This file define some templates about randomness.
 */

namespace mp
{
    /** \class Random
     * \brief A static class with various functions and templates about randomness.
     */

    class Random
    {
        public:
            /** \brief Use this template for integer values (int or long int).
             *
             * \param minN : the minimum value.
             * \param maxN : the maximum value.
             *
             * \return a value between [minN;maxN[
             */
            template<typename T> static T irand(T minN, T maxN);

            /** \brief Use this template for decimal values (float or double).
             *
             * \param minN : the minimum value.
             * \param maxN : the maximum value.
             *
             * \return a decimal value between [minN;maxN[
             */
            template<typename T> static T drand(T minN, T maxN);

            /** \brief Use this template to pick a random element from a vector.
             *
             * \param vec : a vector 
             *
             * \return a random element from the given vector.
             */
            template<typename T> static T vrand(std::vector<T> vec);
    };
}

#endif // RANDOM_HPP_INCLUDED