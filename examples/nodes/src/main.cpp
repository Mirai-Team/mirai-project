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

#include <cmath>
#include <iostream>
#include <memory>

#include <MiraiProject/util/WindowManager.hpp>
#include <MiraiProject/util/StringUtilities.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>

#include "NodeCircle.hpp"

using namespace std;

int main()
{
    cout << "Starting example." << endl;

    bool running{ true };

    mp::WindowManager mainWindowManager { };
    sf::RenderWindow &window = mainWindowManager.getWindow();

    mainWindowManager.setWindowName("Nodes example");
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

    // Creating circles to draw
    cout << "Creating nodes." << endl;

    std::vector<NodeCircle::childPtr> circles{ };
    NodeCircle::childPtr initPtr{ new NodeCircle(60.f) };
    initPtr->setPosition(250, 250);
    initPtr->setName("circle 0");
    cout << "Adding node " << initPtr->getName() << "." << endl;

    circles.push_back(initPtr);
    for (unsigned int i = 1; i < 6; i++)
    {
        NodeCircle::childPtr ptr{ new NodeCircle(50.f / static_cast<float>(i)) };
        ptr->circle.setFillColor(
                                 sf::Color(static_cast<char>(200 - i * 25),
                                           static_cast<char>(200 - i * 25),
                                           static_cast<char>(200 - i * 25))
                                );
        ptr->setName("circle " + mp::StringUtilities::toString(i));
        cout << "Adding node " << ptr->getName() << "." << endl;

        circles.push_back(ptr);
        circles[i - 1]->addFrontChild(circles[i]);
    }

    float theta{ 0.f };

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

        theta += 0.01f;

        // Some logic
        float factor{ 0.f };
        for (unsigned int i = 1; i < circles.size(); i++)
        {
            factor = static_cast<float>(i);

            if (i % 2 == 0)
                factor = -factor;

            circles[i]->setPosition(100 / factor * cos(theta * factor),
                                    100 / factor * sin(theta * factor));
        }

        window.clear(sf::Color::Black);

        window.draw(*circles[0]);

        mainWindowManager.drawBorders(); // Draw the borders.
        window.display();
    }

    // Closing the window if necessary.
    if (window.isOpen())
        window.close();

    cout << "Example stopped." << endl;

    return 0;
}
