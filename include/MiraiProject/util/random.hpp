#ifndef RANDOM_HPP_INCLUDED
#define RANDOM_HPP_INCLUDED

#include <iostream>
#include <chrono>
#include <random>
#include <vector>

#include "MiraiProject/util/random.tpp"

/** @file random.hpp
 * \brief This file define some templates about randomness.
 */
 
namespace mp
{
	/** \brief Use this template for integer values (int or long int).
	 *
     * \param minN : the minimum value.
     * \param maxN : the maximum value.
	 *
     * \return a value between [minN;maxN[
     */
	template<typename T> T irand(T minN, T maxN);
	
	/** \brief Use this template for decimal values (float or double).
	 *
     * \param minN : the minimum value.
     * \param maxN : the maximum value.
	 *
     * \return a decimal value between [minN;maxN[
     */
	template<typename T> T drand(T minN, T maxN);
	
	/** \brief Use this template to pick a random element from a vector.
	 *
     * \param vec : a vector 
	 *
     * \return a random element from the given vector.
     */
	template<typename T> T vrand(std::vector<T> vec);
}

#endif // RANDOM_HPP_INCLUDED
