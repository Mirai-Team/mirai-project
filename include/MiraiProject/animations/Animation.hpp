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
	/** \class Animation
	 * \brief A class to modelize animations for AnimatedSprite.
	 */
	
 	class Animation
	{
		friend class AnimatedSprite;
		
		public:				
			/** \brief Constructor. 
			 *
			 * \param name : the animation name.
			 * \param numStartingFrame : the number of the first animation's frame (on the sprite sheet).
			 * \param numEndingFrame : the number of the last animation's frame (on the sprite sheet).
			 */
			Animation(const std::string& name="NA", const int& numStartingFrame=0,  const int& numEndingFrame=0);
		
			/** \brief Destructor. */
			~Animation();
			
			/////////////
			// Getters //
			/////////////
			
			/** \brief Return the animation's name.
			 *
			 * \return the animation's name.
			 */
			std::string getName() const;
			
			/** \brief Return the starting frame's number for the animation.
			 *
			 * \return the number starting frame's number for the animation.
			 */
			int getNumStartingFrame() const;
			
			/** \brief Return the ending frame's number for the animation.
			 *
			 * \return the number ending frame's number for the animation.
			 */
			int getNumEndingFrame() const;
			
			/** \brief Return the number of frames for the animation.
			 *
			 * \return the number of frames for the animation.
			 */
			int getNumFrames() const;
			
			/** \brief Return the duration of the animation.
			 *
			 * \return the duration of the animation.
			 */
			sf::Time getDuration() const;
			
			/** \brief Return the time per frame of the animation.
			 *
			 * \return the time per frame of the animation.
			 */
			sf::Time getTimePerFrame() const;
			
			/////////////
			// Setters //
			/////////////
			
			/** \brief Set a new name for the animation.
			 *
			 * \param newName : the new name for the animation.
			 */
			void setName(const std::string& newName);
			
			/** \brief Set the new starting frame's number for the animation.
			 *
			 * \param newNumStartingFrame : the new starting frame's number for the animation.
			 */
			void setNumStartingFrame(const int& newNumStartingFrame);
			
			/** \brief Set the new ending frame's number for the animation.
			 *
			 * \param newNumStartingFrame : the new ending frame's number for the animation.
			 */
			void setNumEndingFrame(const int& newNumEndingFrame);
			
			/** \brief Set the new duration for the animation.
			 *
			 * \param newNumStartingFrame : the new duration for the animation.
			 */
			void setDuration(const sf::Time& newDuration);
			
			/** \brief Set the new time per frame for the animation.
			 *
			 * \param newNumStartingFrame : the new time per frame for the animation.
			 */
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
