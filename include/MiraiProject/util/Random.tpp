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

#ifndef RANDOM_TPP_INCLUDED
#define RANDOM_TPP_INCLUDED

#include <iostream>
#include <chrono>
#include <random>
#include <vector>

#include "MiraiProject/util/random.tpp"

using namespace std;

namespace mp
{
    template<typename T> T Random::vrand(vector<T> vec)
    {
        long unsigned int maxN = vec.size();
        unsigned seed = static_cast<unsigned>(chrono::system_clock::now().time_since_epoch().count());
        mt19937 generator (seed);

        return vec[ static_cast<long unsigned int>( generator()%maxN ) ];
    }

    template<typename T> T Random::irand(T minN, T maxN)
    {
        unsigned seed = static_cast<unsigned>(chrono::system_clock::now().time_since_epoch().count());
        mt19937 generator (seed);

        return static_cast<T>(generator()%(maxN - minN) + minN);
    }

    template<typename T> T Random::drand(T minN, T maxN)
    {
        unsigned seed = static_cast<unsigned>(chrono::system_clock::now().time_since_epoch().count());
        mt19937 generator (seed);

        T temp = static_cast<T>(generator())/static_cast<T>(generator.max());
        return (temp * (maxN-minN) + minN);
    }
}

#endif // RANDOM_TPP_INCLUDED