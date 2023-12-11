#pragma once
class ISceneDependant
{
public:
	ISceneDependant();
	virtual ~ISceneDependant();

protected:
	virtual void _OnSceneChange() {};
};