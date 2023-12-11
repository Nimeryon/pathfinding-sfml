#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

class Scene
{
public:
	virtual ~Scene() = default;

	virtual void Init() {}

	virtual void ProcessInputs() {}

	virtual void Update(const sf::Time& dt) {}
	virtual void FixedUpdate(const sf::Time& dt) {}

	virtual void ImGui(const sf::Time& dt) {}

	virtual void Draw(sf::RenderWindow& window) {}
};
