#pragma once
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Text.hpp >

#include "ISceneDependant.h"
#include "Scene.h"
#include "Game.h"

class DefaultScene : public Scene, public ISceneDependant
{
public:
	void Init() override;
	void Draw(sf::RenderWindow& window) override;
	void SetText();

private:
	sf::Text title;
	sf::Text subText;

	sf::Font font;
};
