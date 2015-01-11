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

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Time.hpp>

/** @file AnimatedSprite.hpp
 * \brief This file define AnimatedSprite class.
 */

namespace mp
{
	class AnimatedSprite : public sf::Drawable, public sf::Transformable
	{
		public:
			/** \brief Constructor */
			AnimatedSprite();
			
			AnimatedSprite(const sf::Texture& texture);

			/** \brief Destructor */
			virtual ~AnimatedSprite();
			
			void update(sf::Time dt);
			
			/////////////
			// Getters //
			/////////////
			
			sf::Vector2i getFrameSize() const;
			
			int getNumFrames() const;
			
			int getCurrentFrame() const;
			
			bool isRepeating() const;
			
			sf::Time getDuration() const;
			
			sf::Time getTimePerFrame() const;
			
			bool isFinished() const;

			const sf::Texture* getTexture() const;

			sf::FloatRect getLocalBounds() const;

			sf::FloatRect getGlobalBounds() const;
			
			/////////////
			// Setters //
			/////////////
			
			void setFrameSize(sf::Vector2i newFrameSize);
			
			void setNumFrames(int newNumFrames);
			
			void setCurrentFrame(int newCurrentFrame);
			
			void restart();
			
			void setRepeating(bool newRepeat);
			
			void setDuration(sf::Time newDuration);
			
			void setTimePerFrame(sf::Time newTimePerFrame);

			void setTexture(const sf::Texture& texture);
			
		private:
			sf::Sprite sprite;
			
			sf::Vector2i frameSize;
			
			int numFrames;
			int currentFrame;
			
			bool repeat;
			
			sf::Time duration;
			sf::Time timePerFrame;
			sf::Time elapsedTime;
			
			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	};
}

#endif // ANIMATEDSPRITE_HPP_INCLUDED
