////////////////////////////////////////////////////////////
//
// MiraiProject
// Copyright (C) 2014-2015 CORTIER Benoît (benoit.cortier@gmail.com),
//                         BOULMIER Jérôme (jerome.boulmier@outlook.fr)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the
// use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
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

#ifndef MP_RANDOM_HPP_INCLUDED
#define MP_RANDOM_HPP_INCLUDED

#include <chrono>
#include <iostream>
#include <random>
#include <vector>

/** @file random.hpp
 * \brief This file define some templates about randomness.
 */

namespace mp {
/** \brief Return a random int value.
 *
 * \param min : the minimum value.
 * \param max : the maximum value.
 *
 * \return a value between [min;max]
 */
template <typename T,
    typename std::enable_if<std::is_integral<T>::value>::type = 0>
T getRand(T min, T max);

/** \brief Return a random floating value.
 *
 * \param min : the minimum value.
 * \param max : the maximum value.
 *
 * \return a value between [min;max]
 */
template <typename T,
    typename std::enable_if<std::is_floating_point<T>::value>::type = 0>
T getRand(T min, T max);

/** \brief Use this template to pick a random element from a vector.
 *
 * \param vec : a vector
 *
 * \return a random element from the given vector.
 */
template <typename U, typename T>
T getVRand(U<T> vec);
}

#include <MiraiProject/util/Random.tpp>

#endif // MP_RANDOM_HPP_INCLUDED
