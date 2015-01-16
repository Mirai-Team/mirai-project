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

#include <memory>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Time.hpp>

#include "character.hpp"

using namespace std;

Character::Character(std::shared_ptr<sf::Texture> spriteSheet) :
	mp::AnimatedSprite(*spriteSheet),
	
	speed_{ 0.7f },
	lastPosition_{ getPosition() },
	
	movingLeft{ false },
	movingRight{ false },
	movingDown{ false },
	movingUp{ false }
{
	setFrameSize(sf::Vector2i(32, 36));
	setDefaultTimePerFrame(sf::seconds(0.2f));
	
	addAnimation("up", 0, 3);
	addAnimation("right", 4, 7);
	addAnimation("down", 8, 11);
	addAnimation("left", 12, 15);
}

void Character::update(sf::Time dt)
{
	mp::AnimatedSprite::update(dt);
	
	if (lastPosition_ == getPosition())
	{
		setRepeating(false);
		setCurrentFrame(3);
		
		movingLeft = false;
		movingRight = false;
		movingUp = false;
		movingDown = false;
	}
	else
		setRepeating(true);
	
	lastPosition_ = getPosition();
}

void Character::moveRight()
{
	movingRight = true;
	
	if (getCurrentAnimation() != 1)
		setCurrentAnimation(1);
	
	move(speed_, 0);
}

void Character::moveLeft()
{
	if (!movingRight)
	{
		movingLeft = true;
		
		if (getCurrentAnimation() != 3)
			setCurrentAnimation(3);
		
		move(-speed_, 0);
	}
}

void Character::moveUp()
{
	if (!movingRight and !movingLeft)
	{
		movingUp = true;
	
		if (getCurrentAnimation() != 0)
			setCurrentAnimation(0);
	
		move(0, -speed_);
	}
}

void Character::moveDown()
{
	if (!movingRight and !movingLeft and !movingUp)
	{
		movingDown = true;
		
		if (getCurrentAnimation() != 2)
			setCurrentAnimation(2);
		
		move(0, speed_);
	}
}
