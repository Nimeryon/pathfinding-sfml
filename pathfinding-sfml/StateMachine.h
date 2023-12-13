#pragma once
namespace sf
{
	class Event;
	class Time;
}

namespace sf
{
	class RenderWindow;
}
#include <memory>
#include <stack>
#include <mutex>

#include "Delegate.h"

class Scene;
typedef std::unique_ptr<Scene> SceneRef;

class StateMachine
{
public:
	static StateMachine* Instance();

	StateMachine(StateMachine const&) = delete;
	void operator=(StateMachine const&) = delete;

	void SetScene(SceneRef state);

	void HandleStateUpdate();

	void ProcessInput(const sf::Event& event);
	// Called every drawn frame
	void Update(const sf::Time& dt);
	// Called every logic update (default 60 times a second
	void FixedUpdate(const sf::Time& fixedDt);
	void Draw(sf::RenderWindow& window);

	SceneRef& GetScene();

	static Delegate<> stateChange;

protected:
	StateMachine();
	~StateMachine();

private:
	static StateMachine* _instance;
	static std::mutex _mutex; // For allowing multithreaded use

	std::stack<SceneRef> _scenes;
	SceneRef _scene;

	bool _isSetting;

	void _HandleStateChange();
};