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

#ifndef CHARACTER_HPP_INCLUDED
#define CHARACTER_HPP_INCLUDED

#include <memory>

#include <SFML/System/Vector2.hpp>
#include <SFML/System/Time.hpp>
#include <MiraiProject/animations/AnimatedSprite.hpp>

class Character : public mp::AnimatedSprite
{
	public:
		Character(std::shared_ptr<sf::Texture> spriteSheet);
		
		void update(sf::Time dt);
		
		void moveRight();
		void moveLeft();
		void moveUp();
		void moveDown();
		
	private:
		float speed_;
		
		sf::Vector2f lastPosition_;
		
		bool movingLeft;
		bool movingRight;
		bool movingDown;
		bool movingUp;
};


#endif // CHARACTER_HPP_INCLUDED
