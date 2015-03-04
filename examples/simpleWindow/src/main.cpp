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

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <MiraiProject/util/WindowManager.hpp>

using namespace std;

int main()
{
    cout << "Starting example." << endl;

    bool running{ true };

    mp::WindowManager mainWindowManager { };
    sf::RenderWindow &window = mainWindowManager.getWindow();

    mainWindowManager.setWindowName("Simple Window example");
    mainWindowManager.setOptimalWinWidth(500);
    mainWindowManager.setOptimalWinHeight(500);
    
    // Deliberately set a video mode different from the optimal window dimensions (to show borders).
    mainWindowManager.setVideomodeWidth(750);
    mainWindowManager.setVideomodeHeight(600);
    
    // Set borders' colour.
    mainWindowManager.setBordersColor(sf::Color::White);

    cout << "Creating the main window." << endl;
    mainWindowManager.create();

    // Useful only for testing purpose, but not very effective for real games.
    window.setFramerateLimit(60);

    // Creating a small circle to draw.
    sf::CircleShape shape(25);
    shape.setFillColor(sf::Color(255, 255, 255));
    shape.setPosition(5, 5);

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

        window.clear(sf::Color::Black);
        window.draw(shape);
        mainWindowManager.drawBorders(); // Draw the borders.
        window.display();
    }
    
    // Closing the window if necessary.
    if (window.isOpen())
        window.close();

    cout << "Example stopped." << endl;

    return 0;
}