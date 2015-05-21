#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include <MiraiProject/gui/Border.hpp>
#include <MiraiProject/gui/Button.hpp>
#include <MiraiProject/gui/CheckBox.hpp>
#include <MiraiProject/gui/Label.hpp>
#include <MiraiProject/gui/TextBox.hpp>
#include <MiraiProject/resourcesManagers/AutoResManager.hpp>
#include <MiraiProject/util/WindowManager.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

int main()
{
    bool running = true;

    mp::AutoResManager resourcesManager;
    mp::WindowManager mainWindowManager { };
    sf::RenderWindow &window = mainWindowManager.getWindow();

    mainWindowManager.setWindowName("Gui examples");
    mainWindowManager.setOptimalWinWidth(800);
    mainWindowManager.setOptimalWinHeight(600);
    mainWindowManager.setVideomodeWidth(800);
    mainWindowManager.setVideomodeHeight(600);
    mainWindowManager.setCursorVisible(true);
    mainWindowManager.create();

    mp::Label* label = new mp::Label();
    label->setText(L"Mirai Project Logo");
    label->setPosition(10, 10);
    label->setFont(*resourcesManager.getFontBuffer("resources/UbuntuMono-R.ttf"));
    label->setCharacterSize(20);
    label->setColor(sf::Color::Black);
    label->setPosition(0, -15);
    mp::Label::childPtr labelNode(label);

    mp::Border* border = new mp::Border();
    border->createRectangle(220.f, 220.f, sf::Color::Green);
    border->createBlank(mp::Border::Edge::Bottom, 100, 10);
    border->createBlank(mp::Border::Edge::Left, 100, 10);
    border->setPosition(-10.f, -10.f);
    mp::Border::childPtr borderNode(border);

    // Creating a text box.
    mp::TextBox textBox;
    textBox.setNormalTexture(resourcesManager.getTexture("resources/textBoxNormal.png"));
    textBox.setFocusTexture(resourcesManager.getTexture("resources/textBoxFocus.png"));
    textBox.setHoverTexture(resourcesManager.getTexture("resources/textBoxHover.png"));
    textBox.setPosition(280.f, 5.f);
    textBox.setFont(*resourcesManager.getFontBuffer("resources/UbuntuMono-R.ttf"));
    textBox.setText(L"Some text.");
    textBox.setLabelPos(5, 5);
    textBox.setMaxSize(32);

    // Creating a bigger text box.
    mp::TextBox bigTextBox;
    bigTextBox.setNormalTexture(resourcesManager.getTexture("resources/bigTextBoxNormal.png"));
    bigTextBox.setFocusTexture(resourcesManager.getTexture("resources/bigTextBoxFocus.png"));
    bigTextBox.setHoverTexture(resourcesManager.getTexture("resources/bigTextBoxHover.png"));
    bigTextBox.setPosition(280.f, 60.f);
    bigTextBox.setFont(*resourcesManager.getFontBuffer("resources/UbuntuMono-R.ttf"));
    bigTextBox.setText(L"Some text\non several lines. tête");
    bigTextBox.enableMultiline();
    bigTextBox.setLabelPos(5, 5);

    mp::Button button;
    button.setNormalTexture(resourcesManager.getTexture("resources/logo.png"));
    button.setDownTexture(resourcesManager.getTexture("resources/logoD.png"));
    button.setHoverTexture(resourcesManager.getTexture("resources/logoH.png"));
    button.setPosition(45.f, 45.f);
    button.setFunction([&textBox]() { textBox.setText("Mirai Project"); });
    button.addFrontChild(labelNode);
    button.addFrontChild(borderNode);

    mp::CheckBox checkbox;
    checkbox.setNormalTexture(resourcesManager.getTexture("resources/checkboxNormal.png"));
    checkbox.setHoverTexture(resourcesManager.getTexture("resources/checkboxHover.png"));
    checkbox.setDownTexture(resourcesManager.getTexture("resources/checkboxDown.png"));
    checkbox.setCheckedTexture(resourcesManager.getTexture("resources/checkboxNormalCheck.png"));
    checkbox.setCheckedHoverTexture(resourcesManager.getTexture("resources/checkboxHoverCheck.png"));
    checkbox.setCheckedDownTexture(resourcesManager.getTexture("resources/checkboxDownCheck.png"));
    checkbox.setPosition(20.f, 300.f);

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
                case sf::Event::TextEntered:
                    textBox.handleInput(event.text.unicode);
                    bigTextBox.handleInput(event.text.unicode);
                    break;
                default:
                    break;
            }
        }

        button.update(sf::Mouse::getPosition(window));
        checkbox.update(sf::Mouse::getPosition(window));
        textBox.update(sf::Mouse::getPosition(window));
        bigTextBox.update(sf::Mouse::getPosition(window));

        window.clear(sf::Color(132, 150, 150));

        window.draw(button);
        window.draw(checkbox);
        window.draw(textBox);
        window.draw(bigTextBox);

        window.display();
    }
    
    // Closing the window if necessary.
    if (window.isOpen())
        window.close();

    return 0;
}