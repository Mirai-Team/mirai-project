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

#ifndef ANIMATEDSPRITE_HPP_INCLUDED
#define ANIMATEDSPRITE_HPP_INCLUDED

#include <string>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Time.hpp>

#include "MiraiProject/animations/Animation.hpp"

/** @file AnimatedSprite.hpp
 * \brief This file define AnimatedSprite class.
 */

namespace mp
{
	/** \class AnimatedSprite
	 * \brief A class to handle animated sprites easily by using textures from sprite sheets.
	 */
	
	class AnimatedSprite : public sf::Drawable, public sf::Transformable
	{
		friend class Animation;
		
		public:
			/** \brief Constructor */
			AnimatedSprite();
			
			/** \brief Constructor with texture initialization 
			 *
			 * \param texture : the texture.
			 */
			AnimatedSprite(const sf::Texture& texture);

			/** \brief Destructor */
			virtual ~AnimatedSprite();
			
			/** \brief Update animated sprite current frame.
			 *
			 * \param dt : the delta time since last update.
			 */
			void update(sf::Time dt);
			
			/** \brief Add an animation by giving the starting and ending frame.
			 *
			 * \param numStartingFrame : the starting frame's number.
			 * \param numEndingFrame : the ending frame's number.
			 */
			void addAnimation(const unsigned int& numStartingFrame, const unsigned int& numEndingFrame);
			
			/** \brief Add an animation by giving the name, the starting frame and the ending frame.
			 *
			 * \param name : the animation's name.
			 * \param numStartingFrame : the starting frame's number.
			 * \param numEndingFrame : the ending frame's number.
			 */
			void addAnimation(const std::string& name, const unsigned int& numStartingFrame, const unsigned int& numEndingFrame);
			
			/** \brief Add an animation directly by giving it.
			 *
			 * \param animation : the animation to add.
			 */
			void addAnimation(const mp::Animation& animation);
			
			/** \brief Remove an animation from the animated sprite.
			 *
			 * \param numAnimation : the animation's number.
			 */
			void removeAnimation(const unsigned int& numAnimation);
			
			/** \brief Remove an animation from the animated sprite.
			 *
			 * \param nameAnimation : the animation's name.
			 */
			void removeAnimation(const std::string& nameAnimation);
			
			/** \brief Get the local bounding rectangle of the entity. 
			 *
			 * The returned rectangle is in local coordinates, which means that it ignores the 
			 * transformations (translation, rotation, scale, ...) that are applied to the entity. 
			 * In other words, this function returns the bounds of the entity in the entity's 
			 * coordinate system (this description comes from SFML documentation).
			 *
			 * \return local bounding rectangle of the entity 
			 */
			sf::FloatRect getLocalBounds() const;

			/** \brief Get the global bounding rectangle of the entity. 
			 *
			 * The returned rectangle is in global coordinates, which means that it takes in 
			 * account the transformations (translation, rotation, scale, ...) that are applied to 
			 * the entity. In other words, this function returns the bounds of the sprite in the 
			 * global 2D world's coordinate system (this description comes from SFML documentation).
			 *
			 * \return global bounding rectangle of the entity.
			 */
			sf::FloatRect getGlobalBounds() const;
			
			/////////////
			// Getters //
			/////////////
			
			/** \brief Get frames size in an integer vector.
			 *
			 * \return the frames size.
			 */
			sf::Vector2i getFrameSize() const;
			
			/** \brief Get the current animation's frames number.
			 *
			 * \return the current animation's frames number.
			 */
			int getNumFrames() const;
			
			/** \brief Get the animation's frames number.
			 *
			 * If numAnimation is superior to the number of animations, it simply 
			 * take in account the last animation's data.
			 *
			 * \param numAnimation : the number of the wanted animation.
			 *
			 * \return the animation's frames number.
			 */
			int getNumFrames(const unsigned int& numAnimation) const;
			
			/** \brief Get the animation's frames number.
			 *
			 * \param nameAnimation : the name of the wanted animation.
			 *
			 * \return the animation's frames number.
			 */
			int getNumFrames(const std::string& nameAnimation) const;
			
			/** \brief Get the current animation's frame number.
			 *
			 * \return the current animation's frame number.
			 */
			int getCurrentFrame() const;
			
			/** \brief Return whether the current animation is ended.
			 *
			 * It can only be true if the repeating is false.
			 *
			 * \return whether the current animation is done.
			 */
			bool isFinished() const;
			
			/** \brief Return the number of animations this animated sprite have.
			 *
			 * \return the number of animations.
			 */
			int getNumAnimations() const;
			
			/** \brief Return the current animation number.
			 *
			 * \return the current animation number.
			 */ 
			int getCurrentAnimation() const;
			
			/** \brief Return whether the animation will repeat or not.
			 *
			 * \return whether the animation will repeat.
			 */
			bool isRepeating() const;
			
			/** \brief Return the current animation's duration.
			 *
			 * \return the current animation's duration.
			 */
			sf::Time getDuration() const;
			
			/** \brief Return the animation's duration.
			 *
			 * If numAnimation is superior to the number of animations, it simply 
			 * take in account the last animation's data.
			 *
			 * \param numAnimation : the animation number.
			 *
			 * \return the duration of the animation matching the given number.
			 */
			sf::Time getDuration(const unsigned int& numAnimation) const;
			
			/** \brief Return the animation's duration.
			 *
			 * \param nameAnimation : the animation name.
			 *
			 * \return the duration of the animation matching the given name.
			 */
			sf::Time getDuration(const std::string& nameAnimation) const;
			
			/** \brief Return the current animation's time per frame.
			 *
			 * \return the current animation's time per frame.
			 */
			sf::Time getTimePerFrame() const;
			
			/** \brief Return the animation's time per frame.
			 *
			 * If numAnimation is superior to the number of animations, it simply 
			 * take in account the last animation's data.
			 *
			 * \param numAnimation : the animation number.
			 *
			 * \return the time per frame of the animation matching the given number.
			 */
			sf::Time getTimePerFrame(const unsigned int& numAnimation) const;
			
			/** \brief Return the animation's time per frame.
			 *
			 * \param nameAnimation : the animation name.
			 *
			 * \return the time per frame of the animation matching the given name.
			 */
			sf::Time getTimePerFrame(const std::string& nameAnimation) const;
			
			/** \brief Return the default time per frame for new animations created by the animated sprite.
			 *
			 * \return the default time per frame.
			 */
			sf::Time getDefaultTimePerFrame() const;
			
			/** \brief Return the animated sprite's texture.
			 *
			 * \return the animated sprite's texture.
			 */
			const sf::Texture* getTexture() const;
			
			/////////////
			// Setters //
			/////////////
			
			/** \brief Set the frame size.
			 *
			 * \param newFrameSize : the new size to set.
			 */
			void setFrameSize(const sf::Vector2i& newFrameSize);
			
			/** \brief Set the current frame.
			 *
			 * \param newCurrentFrame : the new current frame.
			 */
			void setCurrentFrame(const unsigned int& newCurrentFrame);
			
			/** \brief Restart the animation. 
			 *
			 * It simply set the current frame to 0.
			 */
			void restart();
			
			/** \brief Set the current animation by the animation's number.
			 *
			 * If newCurrentAnimation is superior to the number of animations, it simply 
			 * take the last animation's number.
			 *
			 * \param newCurrentAnimation : the new animation's number to set.
			 */
			void setCurrentAnimation(const unsigned int& newCurrentAnimation);
			
			/** \brief Set the current animation by the animation's name.
			 *
			 * \param nameAnimation : the new animation's name to set.
			 */
			void setCurrentAnimation(const std::string& nameAnimation);
			
			/** \brief Set whether the animation should loop (repeating).
			 *
			 * \param newRepeat : true to loop, false to stop animation after the last frame.
			 */
			void setRepeating(const bool& newRepeat);
			
			/** \brief Set the duration of the current animation.
			 *
			 * \param newDuration : the new duration.
			 */
			void setDuration(const sf::Time& newDuration);
			
			/** \brief Set the new duration of the animation.
			 *
			 * If numAnimation is superior to the number of animations, it simply 
			 * take in account the last animation's data.
			 *
			 * \param newDuration : the new duration.
			 * \param numAnimation : the number of the animation to modify.
			 */
			void setDuration(const sf::Time& newDuration, const unsigned int& numAnimation);
			
			/** \brief Set the new duration of the animation.
			 *
			 * \param newDuration : the new duration.
			 * \param nameAnimation : the name of the animation to modify.
			 */
			void setDuration(const sf::Time& newDuration, const std::string& nameAnimation);
			
			/** \brief Set the time per frame of the current animation.
			 *
			 * \param newDuration : the new time per frame.
			 */
			void setTimePerFrame(const sf::Time& newTimePerFrame);
			
			/** \brief Set the new time per frame of the animation.
			 *
			 * If numAnimation is superior to the number of animations, it simply 
			 * take in account the last animation's data.
			 *
			 * \param newDuration : the new time per frame.
			 * \param numAnimation : the number of the animation to modify.
			 */
			void setTimePerFrame(const sf::Time& newTimePerFrame, const unsigned int& numAnimation);
			
			/** \brief Set the new time per frame of the animation.
			 *
			 * \param newDuration : the new time per frame.
			 * \param nameAnimation : the name of the animation to modify.
			 */
			void setTimePerFrame(const sf::Time& newTimePerFrame, const std::string& nameAnimation);
			
			/** \brief Set the default time per frame for new animations created by the animated sprite.
			 *
			 * \param newDefaultTimePerFrame : the new default time per frame to set.
			 */
			void setDefaultTimePerFrame(const sf::Time& newDefaultTimePerFrame);
			
			/** \brief Set the animated sprite's texture.
			 *
			 * This texture should be the sprite sheet that you want to use.
			 *
			 * \param the new animated sprite's texture to set.
			 */
			void setTexture(const sf::Texture& texture);
			
		private:
			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
			
			sf::Sprite sprite_;
			
			sf::Vector2i frameSize_;
			
			unsigned int currentFrame_;
			
			unsigned int numAnimations_;
			unsigned int currentAnimation_;
			std::vector<Animation> animations_;
			
			bool repeat_;
			
			sf::Time elapsedTime_;
			sf::Time defaultTimePerFrame_;
	};
}

#endif // ANIMATEDSPRITE_HPP_INCLUDED
