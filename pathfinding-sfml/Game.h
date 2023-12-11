#pragma once
#include <SFML/Graphics.hpp>
#include "Config.h"

struct GameData
{
	GameData(const std::string& filePath = "Assets\\config.json");

	sf::RenderWindow window;
	sf::Time logicTime;
	Config config;
};

typedef std::shared_ptr<GameData> GameDataRef;

class Game
{
public:
	Game(const std::string& title, const sf::Time& logicTime = sf::seconds(1.f / 60.f));
	~Game();

private:
	std::string m_title;

	sf::Clock m_clock;
	sf::Time m_logicUpdateTime;
	GameDataRef m_data = std::make_shared<GameData>();

	void _ProcessInputs() const;
	void _Run();
};