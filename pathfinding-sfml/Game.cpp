#include "Game.h"

#include <imgui-SFML.h>

#include "DefaultScene.h"
#include "StateMachine.h"
#include "Scene.h"

GameData::GameData(const std::string& filePath) :
	config(filePath)
{}

Game::Game(const std::string& title, const sf::Time& logicTime)
{
	const float windowWidth = m_data->config.GetConfig<float>("Window", "Width");
	const float windowHeight = m_data->config.GetConfig<float>("Window", "Height");
	m_data->window.create(
		sf::VideoMode(windowWidth, windowHeight, 1),
		m_title
	);
	m_data->window.setActive(false);

	m_data->logicTime = logicTime;

	ImGui::SFML::Init(m_data->window);

	StateMachine::Instance()->SetScene(std::make_unique<DefaultScene>());

	_Run();
}
Game::~Game()
{
	ImGui::SFML::Shutdown(m_data->window);
}

void Game::_ProcessInputs() const
{
	sf::Event event;
	while (m_data->window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			m_data->window.close();

		StateMachine::Instance()->ProcessInput(event);
		ImGui::SFML::ProcessEvent(m_data->window, event);
	}
}

void Game::_Run()
{
	while (m_data->window.isOpen())
	{
		// Handle clock
		sf::Time time = m_clock.restart();

		// Handle state update
		StateMachine::Instance()->HandleStateUpdate();

		_ProcessInputs();

		// Handle ImGui update
		ImGui::SFML::Update(m_data->window, time);

		StateMachine::Instance()->Update(time);

		// Handle fixed update
		m_logicUpdateTime += time;
		while (m_logicUpdateTime >= m_data->logicTime)
		{
			StateMachine::Instance()->FixedUpdate(m_data->logicTime);
			m_logicUpdateTime -= m_data->logicTime;
		}

		// Handle ImGui call
		StateMachine::Instance()->GetScene()->ImGui(time);

		// Handle rendering
		m_data->window.clear();
		StateMachine::Instance()->Draw(m_data->window);
		ImGui::SFML::Render(m_data->window);
		m_data->window.display();
	}
}
