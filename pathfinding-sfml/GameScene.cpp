#include "GameScene.h"

void GameScene::Init()
{
    obstacle.setRadius(10.f);
    obstacle.setFillColor(sf::Color::Blue);

    initialNode.setFillColor(sf::Color::Green);
    finalNode.setFillColor(sf::Color::Red);
}