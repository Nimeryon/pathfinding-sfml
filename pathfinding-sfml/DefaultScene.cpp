#include "DefaultScene.h"
#include <format>
#include "Config.h"
#include <iostream>

#include "GameScene.h"
#include "imgui-SFML.h"
#include "StateMachine.h"

void DefaultScene::Init()
{
    font.loadFromFile("Assets/Fonts/Roboto-Regular.ttf");
    SetText();
}

void DefaultScene::SetText()
{
    const int windowWidth = Config::GetConfig<int>("Assets\\config.json", "Window", "Width");
    const int windowHeight = Config::GetConfig<int>("Assets\\config.json", "Window", "Height");

    title.setFont(font);
    title.setCharacterSize(windowHeight / 15);
    title.setStyle(sf::Text::Bold);
    title.setString("PATHFINDING");

    float titleX = (windowWidth - title.getLocalBounds().width) / 2;
    float titleY = (windowHeight / 2) - (windowHeight / 10);
    title.setPosition(titleX, titleY);

    subText.setFont(font);
    subText.setCharacterSize(windowHeight / 30);
    subText.setStyle(sf::Text::Italic);
    subText.setString("Press Space to start");

    float subTextX = (windowWidth - subText.getLocalBounds().width) / 2;
    float subTextY = windowHeight / 2;
    subText.setPosition(subTextX, subTextY);

    devName.setFont(font);
    devName.setCharacterSize(windowHeight / 45);
    devName.setString("Mourgues Paul\nPradel Hugo\nAuriol Thomas");

    float nameX = (windowWidth / 40);
    float nameY = (windowHeight - (windowHeight / 10));
    devName.setPosition(nameX, nameY);
}

void DefaultScene::Draw(sf::RenderWindow& window)
{
    window.draw(title);
    window.draw(subText);
    window.draw(devName);
}

void DefaultScene::ProcessInput(const sf::Event& event)
{
    if (event.type == sf::Event::KeyReleased || event.type == sf::Event::MouseButtonPressed)
        if (event.key.code == sf::Keyboard::Space || event.mouseButton.button == sf::Mouse::Left)
			StateMachine::Instance()->SetScene(std::make_unique<GameScene>());
}
