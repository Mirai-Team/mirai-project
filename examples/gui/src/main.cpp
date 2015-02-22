#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include <MiraiProject/gui/Image.hpp>
#include <MiraiProject/gui/Label.hpp>
#include <MiraiProject/resourcesManagers/AutoResManager.hpp>
#include <MiraiProject/util/WindowManager.hpp>

#include <SFML/Graphics.hpp>

int main()
{
    bool running = true;

    mp::AutoResManager resourcesManager;
    mp::WindowManager mainWindowManager { };
    sf::RenderWindow &window = mainWindowManager.getWindow();

    mainWindowManager.setWindowName("Simple Window Test");
    mainWindowManager.setOptimalWinWidth(300);
    mainWindowManager.setOptimalWinHeight(300);
    mainWindowManager.setVideomodeWidth(300);
    mainWindowManager.setVideomodeHeight(300);

    mp::Image image;

    mp::Label* label = new mp::Label();

    label->setText(L"Mirai Project Logo");
    label->setPosition(10, 10);
    label->setFont(*resourcesManager.getFontBuffer("resources/UbuntuMono-R.ttf"));
    label->setCharacterSize(20);
    label->setColor(sf::Color::Red);

    mp::Label::childPtr labelNode(label);
    image.setTexture(*resourcesManager.getTexture("resources/logo.png"));
    image.setPosition(45, 45);
    image.addFrontChild(labelNode);

    // Set borders' colour.
    mainWindowManager.setBordersColor(sf::Color::White);
    mainWindowManager.setCursorVisible(true);
    mainWindowManager.create();

    // Useful only for testing purpose, but not very effective for real games.
    window.setFramerateLimit(60);

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

        window.clear(sf::Color::Blue);
        window.draw(image);
        window.display();
    }
    
    // Closing the window if necessary.
    if (window.isOpen())
        window.close();

    return 0;
}