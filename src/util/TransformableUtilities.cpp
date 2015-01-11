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

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include "MiraiProject/util/TransformableUtilities.hpp"
#include "MiraiProject/animations/AnimatedSprite.hpp"

using namespace std;

void mp::TransformableUtilities::centerOrigin(sf::Sprite& sprite)
{
	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(floor(bounds.left + bounds.width / 2.f), floor(bounds.top + bounds.height / 2.f));
}

void mp::TransformableUtilities::centerOrigin(mp::AnimatedSprite& animatedSprite)
{
	sf::FloatRect bounds = animatedSprite.getLocalBounds();
	animatedSprite.setOrigin(floor(bounds.left + bounds.width / 2.f), floor(bounds.top + bounds.height / 2.f));
}

void mp::TransformableUtilities::centerOrigin(sf::Text& text)
{
	sf::FloatRect bounds = text.getLocalBounds();
	text.setOrigin(floor(bounds.left + bounds.width / 2.f), floor(bounds.top + bounds.height / 2.f));
}
