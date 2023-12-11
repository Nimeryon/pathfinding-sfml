#pragma once
#include <SFML/Graphics/CircleShape.hpp>

#include "ISceneDependant.h"
#include "Scene.h"

class DefaultScene : public Scene, public ISceneDependant
{
public:
	void Init() override;
	void ImGui(const sf::Time& dt) override;
	void Draw(sf::RenderWindow& window) override;

private:
	sf::CircleShape shape;
};
