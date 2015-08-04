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

#ifndef MP_RANDOM_TPP_INCLUDED
#define MP_RANDOM_TPP_INCLUDED

#include <chrono>
#include <iostream>
#include <random>
#include <vector>

namespace mp {
template <typename T,
    typename std::enable_if<std::is_integral<T>::value, int>::type = 0>
T getRand(T min, T max)
{
    assert(min <= max);

    std::mt19937 generator(
        std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<T> distribution(min, max);

    return distribution(generator);
}

template <typename T,
    typename std::enable_if<std::is_floating_point<T>::value, int>::type = 0>
T getRand(T min, T max)
{
    assert(min <= max);

    std::mt19937 generator(
        std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_real_distribution<T> distribution(min, max);

    return distribution(generator);
}

template <typename U, typename T>
T getVRand(U<T> vec)
{
    std::mt19937 generator(
        std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<T> distribution(0, vec.size());

    return vec[distribution(generator)];
}
}

#endif // MP_RANDOM_TPP_INCLUDED
