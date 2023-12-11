#include "ISceneDependant.h"
#include "StateMachine.h"

ISceneDependant::ISceneDependant()
{
	StateMachine::stateChange.Subscribe(this, &ISceneDependant::_OnSceneChange);
}
ISceneDependant::~ISceneDependant()
{
	StateMachine::stateChange.UnSubscribe(this, &ISceneDependant::_OnSceneChange);
}