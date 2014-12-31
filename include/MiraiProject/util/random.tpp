#ifndef RANDOM_TPP_INCLUDED
#define RANDOM_TPP_INCLUDED

#include <iostream>
#include <chrono>
#include <random>
#include <vector>

using namespace std;

namespace mp
{
	template<typename T> T vrand(vector<T> vec)
	{
		long unsigned int maxN = vec.size();
		unsigned seed = static_cast<unsigned>(chrono::system_clock::now().time_since_epoch().count());
		mt19937 generator (seed);
	
		return vec[ static_cast<long unsigned int>( generator()%maxN ) ];
	}
	
	template<typename T> T irand(T minN, T maxN)
	{
		unsigned seed = static_cast<unsigned>(chrono::system_clock::now().time_since_epoch().count());
		mt19937 generator (seed);

		return static_cast<T>(generator()%(maxN - minN) + minN);
	}
	
	template<typename T> T drand(T minN, T maxN)
	{
		unsigned seed = static_cast<unsigned>(chrono::system_clock::now().time_since_epoch().count());
		mt19937 generator (seed);
		
		T temp = static_cast<T>(generator())/static_cast<T>(generator.max());
		return (temp * (maxN-minN) + minN);
	}

}

#endif // RANDOM_TPP_INCLUDED
