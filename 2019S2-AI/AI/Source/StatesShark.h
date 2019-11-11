#pragma once
#include "State.h"
#include "GameObject.h"

class StateCrazy : public State
{
	GameObject* m_go;
public:
	StateCrazy(const std::string& stateID, GameObject* go);
	virtual ~StateCrazy();

	virtual void Enter();
	virtual void Update(double dt);
	virtual void Exit();
};

class StateNaughty : public State
{
	GameObject* m_go;
public:
	StateNaughty(const std::string& stateID, GameObject* go);
	virtual ~StateNaughty();

	virtual void Enter();
	virtual void Update(double dt);
	virtual void Exit();
};

class StateHappy : public State
{
	GameObject* m_go;
public:
	StateHappy(const std::string& stateID, GameObject* go);
	virtual ~StateHappy();

	virtual void Enter();
	virtual void Update(double dt);
	virtual void Exit();
};