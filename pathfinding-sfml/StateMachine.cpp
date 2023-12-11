#include "StateMachine.h"
#include "Scene.h"

StateMachine* StateMachine::_instance = nullptr;
std::mutex StateMachine::_mutex;

Delegate<> StateMachine::stateChange;

StateMachine* StateMachine::Instance()
{
	std::lock_guard lock(_mutex);

	if (!_instance) _instance = new StateMachine();
	return _instance;
}

StateMachine::StateMachine() :
	_scene(nullptr),
	_isSetting(false)
{}
StateMachine::~StateMachine() = default;

void StateMachine::SetScene(SceneRef state)
{
	_isSetting = true;
	_scene = std::move(state);
}

void StateMachine::HandleStateUpdate()
{
	_HandleStateChange();
}

void StateMachine::ProcessInputs()
{
	GetScene()->ProcessInputs();
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

SceneRef& StateMachine::GetScene() { return _scenes.top(); }

void StateMachine::_HandleStateChange()
{
	if (!_isSetting) return;

	stateChange();

	_scenes.push(std::move(_scene));
	_scenes.top()->Init();
	_isSetting = false;
}