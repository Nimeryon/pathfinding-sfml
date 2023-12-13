#include "DefaultScene.h"
#include <format>
#include "Config.h"
#include <iostream>

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
    title.setPosition(10, 10);
    title.setCharacterSize(24);
    title.setString("PATH FIND ING");
    title.setFillColor(sf::Color::White);

    subText.setFont(font);
    subText.setPosition(windowWidth, windowHeight);
    subText.setCharacterSize(windowHeight / 30);
    title.setString("Press 'Space' to start");
}


void DefaultScene::Draw(sf::RenderWindow& window)
{
    window.draw(title);
    window.draw(subText);
}