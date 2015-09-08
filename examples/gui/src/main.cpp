#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include <MiraiProject/scene/Node.hpp>
#include <MiraiProject/gui/Bar.hpp>
#include <MiraiProject/gui/Border.hpp>
#include <MiraiProject/gui/Button.hpp>
#include <MiraiProject/gui/CheckBox.hpp>
#include <MiraiProject/gui/Label.hpp>
#include <MiraiProject/gui/TextBox.hpp>
#include <MiraiProject/gui/TrackBar.hpp>
#include <MiraiProject/resourcesManagers/AutoResManager.hpp>
#include <MiraiProject/util/WindowManager.hpp>
#include <MiraiProject/util/StringUtilities.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

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

    mp::Bar bar;
    bar.setPosition(0, 400);
    bar.setTexture(resourcesManager.getTexture("resources/progressBar.png"));
    bar.setSize(sf::Vector2u(200, 20));
    bar.setMin(20.f);
    bar.setMax(200.f);
    bar.setValue(90.f);

    mp::Label* label = new mp::Label();
    label->setString(L"Mirai Project Logo");
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
    mp::Border::childPtr borderNode { border };

    // Creating a text box.
    mp::TextBox textBox;
    textBox.setNormalTexture(resourcesManager.getTexture("resources/textBoxNormal.png"));
    textBox.setFocusTexture(resourcesManager.getTexture("resources/textBoxFocus.png"));
    textBox.setHoverTexture(resourcesManager.getTexture("resources/textBoxHover.png"));
    textBox.setPosition(280.f, 5.f);
    textBox.setFont(*resourcesManager.getFontBuffer("resources/UbuntuMono-R.ttf"));
    textBox.setString(L"Some text.");
    textBox.setTextPos(5, 5);
    textBox.setMaxSize(32);
    textBox.setCharacterSize(30);

    // Creating a bigger text box.
    mp::TextBox bigTextBox;
    bigTextBox.setNormalTexture(resourcesManager.getTexture("resources/bigTextBoxNormal.png"));
    bigTextBox.setFocusTexture(resourcesManager.getTexture("resources/bigTextBoxFocus.png"));
    bigTextBox.setHoverTexture(resourcesManager.getTexture("resources/bigTextBoxHover.png"));
    bigTextBox.setPosition(280.f, 60.f);
    bigTextBox.setFont(*resourcesManager.getFontBuffer("resources/UbuntuMono-R.ttf"));
    bigTextBox.setString(L"Some text\non several lines.");
    bigTextBox.enableMultiline();
    bigTextBox.setTextPos(5, 3);
    bigTextBox.setCharacterSize(18);
    bigTextBox.setMaxWidth(499.f);
    bigTextBox.setMaxHeight(293.f);

    mp::Button button;
    button.setNormalTexture(resourcesManager.getTexture("resources/logo.png"));
    button.setDownTexture(resourcesManager.getTexture("resources/logoD.png"));
    button.setHoverTexture(resourcesManager.getTexture("resources/logoH.png"));
    button.setPosition(45.f, 45.f);
    button.setFunction([&textBox, &bar]() {
        textBox.setString("Mirai Project");
    });
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

    // The first trackbar, on the left.
    mp::TrackBar trackbar;
    trackbar.setNormalTexture(resourcesManager.getTexture("resources/trackbarNormal.png"));
    trackbar.setHoverTexture(resourcesManager.getTexture("resources/trackbarHover.png"));
    trackbar.setDownTexture(resourcesManager.getTexture("resources/trackbarDown.png"));
    trackbar.setOrigin(26, 50); // Set origin to the texture's center.
    trackbar.setExtremPos1({ 50.f, 500.f });
    trackbar.setExtremPos2({ 300.f, 500.f });
    trackbar.setMin(10);
    trackbar.setMax(20);
    trackbar.setValue(5.f);
    trackbar.setAcceptFloat(false);

    mp::Label* trackbarLabel = new mp::Label { };
    trackbarLabel->setFont(*resourcesManager.getFontBuffer("resources/UbuntuMono-R.ttf"));
    trackbarLabel->setCharacterSize(50);
    trackbarLabel->setColor(sf::Color::Black);
    trackbarLabel->setPosition(0, 46);
    mp::Label::childPtr trackbarLabelChild{ trackbarLabel };
    trackbar.addFrontChild(trackbarLabelChild);

    sf::RectangleShape rectangle { sf::Vector2f{ 250, 10 } };
    rectangle.setPosition(50.f, 495.f);

    // The second trackbar, on the right.
    mp::TrackBar trackbar2;
    trackbar2.setNormalTexture(resourcesManager.getTexture("resources/trackbarNormal.png"));
    trackbar2.setHoverTexture(resourcesManager.getTexture("resources/trackbarHover.png"));
    trackbar2.setDownTexture(resourcesManager.getTexture("resources/trackbarDown.png"));
    trackbar2.setOrigin(26, 50);
    trackbar2.setExtremPos1({ 400.f, 510.f });
    trackbar2.setExtremPos2({ 450.f, 410.f });
    trackbar2.setMin(0);
    trackbar2.setMax(10);
    trackbar2.setValue(5.f);
    trackbar2.rotate(-60.f);

    mp::Label* trackbarLabel2 = new mp::Label { };
    trackbarLabel2->setFont(*resourcesManager.getFontBuffer("resources/UbuntuMono-R.ttf"));
    trackbarLabel2->setCharacterSize(50);
    trackbarLabel2->setColor(sf::Color::Black);
    trackbarLabel2->setPosition(0, 46);
    mp::Label::childPtr trackbarLabelChild2{ trackbarLabel2 };
    trackbar2.addFrontChild(trackbarLabelChild2);

    sf::RectangleShape rectangle2 { sf::Vector2f{ 112, 10 } };
    rectangle2.setPosition(395.f, 510.f);
    rectangle2.rotate(-60.f);

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

            textBox.handleInput(event);
            bigTextBox.handleInput(event);
        }

        button.update(sf::Mouse::getPosition(window));
        checkbox.update(sf::Mouse::getPosition(window));
        textBox.update(sf::Mouse::getPosition(window));
        bigTextBox.update(sf::Mouse::getPosition(window));

        trackbar.update(sf::Mouse::getPosition(window));
        trackbarLabel->setString(mp::StringUtilities::toString(trackbar.getValue()));

        trackbar2.update(sf::Mouse::getPosition(window));
        trackbarLabel2->setString(mp::StringUtilities::toString(trackbar2.getValue()));
        bar.setValue(trackbar2.getValue() * 20);

        window.clear(sf::Color(132, 150, 150));

        window.draw(bar);
        window.draw(button);
        window.draw(checkbox);
        window.draw(textBox);
        window.draw(bigTextBox);
        window.draw(rectangle);
        window.draw(trackbar);
        window.draw(rectangle2);
        window.draw(trackbar2);

        window.display();
    }

    // Closing the window if necessary.
    if (window.isOpen())
        window.close();

    return 0;
}
