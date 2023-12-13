#include "StateMachine.h"
#include "Scene.h"

StateMachine* StateMachine::m_instance = nullptr;
std::mutex StateMachine::m_mutex;

Delegate<> StateMachine::stateChange;

StateMachine* StateMachine::Instance()
{
	std::lock_guard lock(m_mutex);

	if (!m_instance) m_instance = new StateMachine();
	return m_instance;
}

StateMachine::StateMachine() :
	m_scene(nullptr),
	m_isSetting(false)
{}
StateMachine::~StateMachine() = default;

void StateMachine::SetScene(SceneRef state)
{
	m_isSetting = true;
	m_scene = std::move(state);
}

void StateMachine::HandleStateUpdate()
{
	_HandleStateChange();
}

void StateMachine::ProcessInput(const sf::Event& event)
{
	GetScene()->ProcessInput(event);
}
void StateMachine::Update(const sf::Time& dt)
{
	GetScene()->Update(dt);
}
void StateMachine::FixedUpdate(const sf::Time& fixedDt)
{
	GetScene()->FixedUpdate(fixedDt);
}
void StateMachine::Draw(sf::RenderWindow& window)
{
	GetScene()->Draw(window);
}

SceneRef& StateMachine::GetScene() { return m_scenes.top(); }

void StateMachine::_HandleStateChange()
{
	if (!m_isSetting) return;

	stateChange();

	m_scenes.push(std::move(m_scene));
	m_scenes.top()->Init();
	m_isSetting = false;
}