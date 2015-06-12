////////////////////////////////////////////////////////////
//
// MiraiProject
// Copyright (C) 2014-2015 CORTIER Benoît (benoit.cortier@gmail.com), BOULMIER Jérôme (jerome.boulmier@outlook.fr)
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

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <MiraiProject/util/WindowManager.hpp>
#include <MiraiProject/animations/Animation.hpp>
#include <MiraiProject/animations/AnimatedSprite.hpp>
#include <MiraiProject/inputManager/KeyboardManager.hpp>
#include <MiraiProject/inputManager/MouseManager.hpp>
#include <MiraiProject/resourcesManagers/AutoResManager.hpp>

#include "character.hpp"

using namespace std;

int main()
{
    cout << "Starting example." << endl;

    bool running{ true };

    // ---------- Creating the window. ----------
    mp::WindowManager mainWindowManager { };
    sf::RenderWindow &window = mainWindowManager.getWindow();

    mainWindowManager.setWindowName("Simple character control");
    mainWindowManager.setOptimalWinWidth(500);
    mainWindowManager.setOptimalWinHeight(500);
    mainWindowManager.setVideomodeWidth(500);
    mainWindowManager.setVideomodeHeight(500);

    cout << "Creating the main window." << endl;
    mainWindowManager.create();

    window.setFramerateLimit(60); // Useful only for testing purpose, but not very effective for real games.
    // ===========================================

    mp::AutoResManager resManager{ };

    // Create the character.
    Character character{ resManager.getTexture("resources/character.png") };
    character.setPosition(200, 200);

    // Creating the keyboard manager.
    mp::KeyboardManager keyboardManager;
    mp::MouseManager mouseManager;

    // We bind the move methods.
    keyboardManager.addBinding("moveRight", sf::Keyboard::Right, [&character](){
        character.moveRight();
    });

    keyboardManager.addBinding("moveLeft", sf::Keyboard::Left, [&character](){
        character.moveLeft();
    });

    keyboardManager.addBinding("moveUp", sf::Keyboard::Up, [&character](){
        character.moveUp();
    });

    keyboardManager.addBinding("moveDown", sf::Keyboard::Down, [&character](){
        character.moveDown();
    });

    mouseManager.addBinding("moveLeft", sf::Mouse::Left, [&character](){
        character.moveLeft();
    });

    mouseManager.addBinding("moveRight", sf::Mouse::Right, [&character](){
        character.moveRight();
    });

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
                case sf::Event::GainedFocus:
                    mouseManager.enable();
                    keyboardManager.enable();
                    break;
                case sf::Event::LostFocus:
                    mouseManager.disable();
                    keyboardManager.disable();
                    break;
                default:
                    break;
            }
        }

        // Checking inputs related to registered actions.
        keyboardManager();
        mouseManager();

        // Updating sprite's animation.
        character.update(sf::seconds(1.f / 60.f));

        window.clear(sf::Color::Black);
        window.draw(character); // Drawing the character.
        window.display();
    }

    // Closing the window if necessary.
    if (window.isOpen())
        window.close();

    cout << "Example stopped." << endl;

    return 0;
}
