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
	class AnimatedSprite : public sf::Drawable, public sf::Transformable
	{
		friend class Animation;
		
		public:
			/** \brief Constructor */
			AnimatedSprite();
			
			AnimatedSprite(const sf::Texture& texture);

			/** \brief Destructor */
			virtual ~AnimatedSprite();
			
			void update(sf::Time dt);
			
			void addAnimation(const int& numStartingFrame, const int& numEndingFrame);
			
			void addAnimation(const std::string& name, const int& numStartingFrame, const int& numEndingFrame);
			
			void addAnimation(const mp::Animation& animation);
			
			sf::FloatRect getLocalBounds() const;

			sf::FloatRect getGlobalBounds() const;
			
			/////////////
			// Getters //
			/////////////
			
			sf::Vector2i getFrameSize() const;
			
			int getNumFrames() const;
			
			int getNumFrames(const int& numAnimation) const;
			
			int getNumFrames(const std::string& nameAnimation) const;
			
			int getCurrentFrame() const;
			
			bool isFinished() const;
			
			int getNumAnimations() const;
			
			int getCurrentAnimation() const;
			
			bool isRepeating() const;
			
			sf::Time getDuration() const;
			
			sf::Time getDuration(const int& numAnimation) const;
			
			sf::Time getDuration(const std::string& nameAnimation) const;
			
			sf::Time getTimePerFrame() const;
			
			sf::Time getTimePerFrame(const int& numAnimation) const;
			
			sf::Time getTimePerFrame(const std::string& nameAnimation) const;

			sf::Time getDefaultTimePerFrame() const;
			
			const sf::Texture* getTexture() const;
			
			/////////////
			// Setters //
			/////////////
			
			void setFrameSize(const sf::Vector2i& newFrameSize);
			
			void setCurrentFrame(const int& newCurrentFrame);
			
			void restart();
			
			void setCurrentAnimation(const int& newCurrentAnimation);
			
			void setCurrentAnimation(const std::string& nameAnimation);
			
			void setRepeating(const bool& newRepeat);
			
			void setDuration(const sf::Time& newDuration);
			
			void setDuration(const sf::Time& newDuration, const int& numAnimation);
			
			void setDuration(const sf::Time& newDuration, const std::string& nameAnimation);
			
			void setTimePerFrame(const sf::Time& newTimePerFrame);
			
			void setTimePerFrame(const sf::Time& newTimePerFrame, const int& numAnimation);
			
			void setTimePerFrame(const sf::Time& newTimePerFrame, const std::string& nameAnimation);

			void setDefaultTimePerFrame(const sf::Time& newDefaultTimePerFrame);
			
			void setTexture(const sf::Texture& texture);
			
		private:
			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
			
			sf::Sprite sprite_;
			
			sf::Vector2i frameSize_;
			
			int currentFrame_;
			
			int numAnimations_;
			int currentAnimation_;
			std::vector<Animation> animations_;
			
			bool repeat_;
			
			sf::Time elapsedTime_;
			sf::Time defaultTimePerFrame_;
	};
}

#endif // ANIMATEDSPRITE_HPP_INCLUDED
