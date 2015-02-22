#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include <MiraiProject/gui/Button.hpp>
#include <MiraiProject/gui/Image.hpp>
#include <MiraiProject/gui/Label.hpp>
#include <MiraiProject/resourcesManagers/AutoResManager.hpp>
#include <MiraiProject/util/WindowManager.hpp>

#include <SFML/Graphics.hpp>

void helloWorld(mp::Label* label)
{
    label->setColor(sf::Color::Green);
}

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

    mp::Button button(window);

    mp::Label* label = new mp::Label();
    label->setText(L"Mirai Project Logo");
    label->setPosition(10, 10);
    label->setFont(*resourcesManager.getFontBuffer("resources/UbuntuMono-R.ttf"));
    label->setCharacterSize(20);
    label->setColor(sf::Color::Red);

    mp::Label::childPtr labelNode(label);
    button.setNormalTexture(*resourcesManager.getTexture("resources/logo.png"));
    button.setDownTexture(*resourcesManager.getTexture("resources/logoD.png"));
    button.setHoverTexture(*resourcesManager.getTexture("resources/logoH.png"));
    button.setPosition(0, 0);
    button.setFunction([&]() { helloWorld(label); });
    button.addFrontChild(labelNode);

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
            button.update();
        }

        window.clear(sf::Color::Blue);
        window.draw(button);
        window.display();
    }
    
    // Closing the window if necessary.
    if (window.isOpen())
        window.close();

    return 0;
}