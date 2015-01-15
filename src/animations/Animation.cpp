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

#include <string>

#include <SFML/System/Time.hpp>

#include "MiraiProject/animations/Animation.hpp"

mp::Animation::Animation(const std::string& name, const unsigned int& numStartingFrame,  const unsigned int& numEndingFrame) :
	name_{ name },
	
	numStartingFrame_{ numStartingFrame },
	numEndingFrame_{ numEndingFrame },
	numFrames_{ numEndingFrame_ - numStartingFrame_ + 1 },
	
	timePerFrame_{ sf::seconds(1) },
	duration_{ sf::Time::Zero }
{
	update();
}

mp::Animation::~Animation()
{
	
}

/////////////
// Getters //
/////////////

std::string mp::Animation::getName() const
{
	return name_;
}
	
unsigned int mp::Animation::getNumStartingFrame() const
{
	return numStartingFrame_;
}

unsigned int mp::Animation::getNumEndingFrame() const
{
	return numEndingFrame_;
}

unsigned int mp::Animation::getNumFrames() const
{
	return numFrames_;
}

sf::Time mp::Animation::getDuration() const
{
	return duration_;
}

sf::Time mp::Animation::getTimePerFrame() const
{
	return timePerFrame_;
}

/////////////
// Setters //
/////////////

void mp::Animation::setName(const std::string& newName)
{
	name_ = newName;
}

void mp::Animation::setNumStartingFrame(const unsigned int& newNumStartingFrame)
{
	numStartingFrame_ = newNumStartingFrame;
	update();
}

void mp::Animation::setNumEndingFrame(const unsigned int& newNumEndingFrame)
{
	numEndingFrame_ = newNumEndingFrame;
	update();
}

void mp::Animation::setDuration(const sf::Time& newDuration)
{
	if (newDuration != sf::Time::Zero) // Duration cannot be null.
		duration_ = newDuration;
	timePerFrame_ = duration_ / static_cast<float>(numFrames_);
}

void mp::Animation::setTimePerFrame(const sf::Time& newTimePerFrame)
{
	if (newTimePerFrame != sf::Time::Zero) // timePerFrame cannot be null.
		timePerFrame_ = newTimePerFrame;
	duration_ = timePerFrame_ * static_cast<float>(numFrames_);
}

/////////////
// Private //
/////////////

void mp::Animation::update()
{
	if (numEndingFrame_ < numStartingFrame_)
		numEndingFrame_ = numStartingFrame_;
	
	numFrames_ = numEndingFrame_ - numStartingFrame_ + 1;
	
	duration_ = timePerFrame_ * static_cast<float>(numFrames_);
}
