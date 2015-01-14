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

#ifndef ANIMATION_HPP_INCLUDED
#define ANIMATION_HPP_INCLUDED

#include <string>

#include <SFML/System/Time.hpp>

/** @file Animation.hpp
 * \brief This file define Animation class.
 */
 
namespace mp
{
 	class Animation
	{
		friend class AnimatedSprite;
		 
		public:				
			/* \brief Constructor with attributes initialization. 
			 *
			 * \param name : the animation name.
			 * \param numStartingFrame : the number of the first animation's frame (on the sprite sheet).
			 * \param numEndingFrame : the number of the last animation's frame (on the sprite sheet).
			 */
			Animation(const std::string& name="NA", const int& numStartingFrame=0,  const int& numEndingFrame=0);
		
			/* \brief Destructor. */
			~Animation();
			
			/////////////
			// Getters //
			/////////////
			
			std::string getName() const;
			
			int getNumStartingFrame() const;
			
			int getNumEndingFrame() const;
			
			int getNumFrames() const;
			
			sf::Time getDuration() const;
			
			sf::Time getTimePerFrame() const;
			
			/////////////
			// Setters //
			/////////////
			
			void setName(const std::string& newName);
			
			void setNumStartingFrame(const int& newNumStartingFrame);
			
			void setNumEndingFrame(const int& newNumEndingFrame);
			
			void setDuration(const sf::Time& newDuration);
			
			void setTimePerFrame(const sf::Time& newTimePerFrame);
		
		private:
			void update();
		
			std::string name_;
		
			int numStartingFrame_;
			int numEndingFrame_;
			int numFrames_;
			
			sf::Time timePerFrame_;
			sf::Time duration_;
	 };
}

#endif // ANIMATION_HPP_INCLUDED
