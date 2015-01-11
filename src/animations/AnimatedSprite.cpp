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

#include <iostream>

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Time.hpp>

#include "MiraiProject/animations/AnimatedSprite.hpp"

mp::AnimatedSprite::AnimatedSprite() :
	sprite{ },
	
	frameSize{ 64, 64 },
	
	numFrames{ 0 },
	currentFrame{ 0 },
	
	repeat{ false },
	
	duration{ sf::Time::Zero },
	timePerFrame{ sf::Time::Zero },
	elapsedTime{ sf::Time::Zero }
{
	
}

mp::AnimatedSprite::AnimatedSprite(const sf::Texture& texture) : 
	sprite{ texture },
	
	frameSize{ 64, 64 },
	
	numFrames{ 0 },
	currentFrame{ 0 },
	
	repeat{ false },
	
	duration{ sf::Time::Zero },
	timePerFrame{ sf::Time::Zero },
	elapsedTime{ sf::Time::Zero }
{
	
}

mp::AnimatedSprite::~AnimatedSprite()
{
	
}

void mp::AnimatedSprite::update(sf::Time dt)
{
	sf::Vector2i textureBounds(sprite.getTexture()->getSize());
	sf::IntRect textureRect{ sprite.getTextureRect() };
	
	elapsedTime += dt;
	
	while (elapsedTime >= timePerFrame and (currentFrame + 1 < numFrames or repeat))
	{
		elapsedTime -= timePerFrame;
		
		if (repeat)
			currentFrame = (currentFrame + 1) % numFrames;
		else
			currentFrame++;
	}
	
	textureRect.left = (frameSize.x * currentFrame) % textureBounds.x;
	textureRect.top = frameSize.y * static_cast<int>((frameSize.x * currentFrame) / textureBounds.x);
	
	if (currentFrame == 0)
		textureRect = sf::IntRect(0, 0, frameSize.x, frameSize.y);
	
	sprite.setTextureRect(textureRect);
}

/////////////
// Getters //
/////////////

sf::Vector2i mp::AnimatedSprite::getFrameSize() const
{
	return frameSize;
}

int mp::AnimatedSprite::getNumFrames() const
{
	return numFrames;
}

int mp::AnimatedSprite::getCurrentFrame() const
{
	return currentFrame;
}

bool mp::AnimatedSprite::isRepeating() const
{
	return repeat;
}

sf::Time mp::AnimatedSprite::getDuration() const
{
	return duration;
}

sf::Time mp::AnimatedSprite::getTimePerFrame() const
{
	return timePerFrame;
}

bool mp::AnimatedSprite::isFinished() const
{
	return currentFrame >= numFrames;
}

const sf::Texture* mp::AnimatedSprite::getTexture() const
{
	return sprite.getTexture();
}

sf::FloatRect mp::AnimatedSprite::getLocalBounds() const
{
	return sf::FloatRect(getOrigin(), static_cast<sf::Vector2f>(getFrameSize()));
}

sf::FloatRect mp::AnimatedSprite::getGlobalBounds() const
{
	return getTransform().transformRect(getLocalBounds());
}

/////////////
// Setters //
/////////////

void mp::AnimatedSprite::setFrameSize(sf::Vector2i newFrameSize)
{
	frameSize = newFrameSize;
}

void mp::AnimatedSprite::setNumFrames(int newNumFrames)
{
	numFrames = newNumFrames;
}

void mp::AnimatedSprite::setCurrentFrame(int newCurrentFrame)
{
	currentFrame = newCurrentFrame;
}

void mp::AnimatedSprite::restart()
{
	currentFrame = 0;
}

void mp::AnimatedSprite::setRepeating(bool newRepeat)
{
	repeat = newRepeat;
}

void mp::AnimatedSprite::setDuration(sf::Time newDuration)
{
	duration = newDuration;
	timePerFrame = duration / static_cast<float>(numFrames);
}

void mp::AnimatedSprite::setTimePerFrame(sf::Time newTimePerFrame)
{
	timePerFrame = newTimePerFrame;
	duration = timePerFrame * static_cast<float>(numFrames);
}

void mp::AnimatedSprite::setTexture(const sf::Texture& texture)
{
	sprite.setTexture(texture);
}

/////////////
// Private //
/////////////

void mp::AnimatedSprite::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(sprite, states);
}
