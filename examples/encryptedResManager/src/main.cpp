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

#include <memory>
#include <fstream>

#include <MiraiProject/encryption/Encryption.hpp>
#include <MiraiProject/resourcesManagers/EncryptedResManager.hpp>
#include <MiraiProject/util/WindowManager.hpp>

#include <boost/filesystem.hpp>

#include <SFML/Graphics.hpp>

using namespace std;

int main()
{
    bool running = true;
    mp::EncryptedResManager ResManager;

    boost::filesystem::path directory("resources/images/");
    mp::Encryption EncryptMotor("MiraiProject");
    EncryptMotor.createFile("resources/data.bin", directory);

    std::shared_ptr<sf::Texture> myTexture{ };
    myTexture = ResManager.getTexture("resources/images/img.jpg", "resources/data.bin", "MiraiProject");

    mp::WindowManager mainWindowManager { };

    sf::RenderWindow &window = mainWindowManager.getWindow();

    mainWindowManager.setWindowName("EncryptedResManager Example");
    mainWindowManager.setOptimalWinWidth(500);
    mainWindowManager.setOptimalWinHeight(500);
    mainWindowManager.setVideomodeWidth(500);
    mainWindowManager.setVideomodeHeight(500);

    mainWindowManager.create();

    sf::Sprite mySprite(*myTexture);

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
        window.draw(mySprite);
        window.display();
    }

    // Closing the window if necessary.
    if (window.isOpen())
        window.close();
    return 0;
}