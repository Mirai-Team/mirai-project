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

#include <MiraiProject/util/WindowManager.hpp>
#include <MiraiProject/animations/AnimatedSprite.hpp>

using namespace std;

int main()
{
	cout << "Starting example." << endl;
	
	bool running{ true };
	
	mp::WindowManager mainWindowManager { };
	sf::RenderWindow &window = mainWindowManager.getWindow();
	
	mainWindowManager.setWindowName("Simple animated sprite test");
	mainWindowManager.setOptimalWinWidth(500);
	mainWindowManager.setOptimalWinHeight(500);
	mainWindowManager.setVideomodeWidth(500);
	mainWindowManager.setVideomodeHeight(500);
	
	cout << "Creating the main window." << endl;
	mainWindowManager.create();
	
	// Useful only for testing purpose, but not very effective for real games.
	window.setFramerateLimit(60);
	
	// Create an animated sprite.
	sf::Texture spriteSheet;
	spriteSheet.loadFromFile("resources/character.png");
	
	mp::AnimatedSprite mySprite{ spriteSheet };
	mySprite.setFrameSize(sf::Vector2i(32, 36));
	mySprite.setNumFrames(4);
	mySprite.setTimePerFrame(sf::seconds(0.2f));
	mySprite.setRepeating(true);
	mySprite.setPosition(200, 200);
	
	while (running)
	{
		// Process events...
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed:
					running = false;
					break;
				default:
					break;
			}
		}
		
		// Updating sprite's animation.
		mySprite.update(sf::seconds(1.f / 60.f));
		mySprite.move(0, -0.7f);
		if (mySprite.getPosition().y < -40)
			mySprite.setPosition(mySprite.getPosition().x, 540);
		
		window.clear(sf::Color::Black);
		window.draw(mySprite); // Drawing the sprite.
		window.display();
	}
	
    // Closing the window if necessary.
    if (window.isOpen())
		window.close();
	
	cout << "Example stopped." << endl;
	
	return 0;
}
