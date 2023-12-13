#pragma once

#include <SFML/Graphics.hpp>

//#include "ISceneDependant.h"
#include "Scene.h"

class GameScene : public Scene
{
public:
	void Init() override;
	void Draw(sf::RenderWindow& window) override;

protected:

	sf::RectangleShape node;
	sf::RectangleShape initialNode;
	sf::RectangleShape finalNode;

	sf::CircleShape obstacle;
};

