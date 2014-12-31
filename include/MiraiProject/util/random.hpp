#ifndef RANDOM_HPP_INCLUDED
#define RANDOM_HPP_INCLUDED

#include <iostream>
#include <chrono>
#include <random>
#include <vector>

#include "MiraiProject/util/random.tpp"

/** @file random.hpp
 * This file define the random templates.
 *
 */
 
namespace mp
{
	/** \brief Use this template for integer number like int or long int.
    * \param minN : the minimum number.
    * \param maxN : the maximum number.
    * \return A number beetween [minN;maxN[
    */
	template<typename T> T irand(T minN, T maxN);
	
	/** \brief Use this template for decimal number like float or double.
    * \param minN : the minimum number.
    * \param maxN : the maximum number.
    * \return A decimal number beetween [minN;maxN[
    */
	template<typename T> T drand(T minN, T maxN);
	
	/** \brief Use this template for pick a random element in a vector.
    * \param vec : A vector 
    * \return A random element of the vector.
    */
	template<typename T> T vrand(std::vector<T> vec);
}

#endif // RANDOM_HPP_INCLUDED
