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

	void ProcessInput(const sf::Event& event) override;

private:
	sf::Text title;
	sf::Text subText;
	sf::Text devName;

	sf::Font font;
};
