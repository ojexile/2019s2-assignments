#pragma once
#include "ScriptComponent.h"

/*
author: lorenzo yanga
desc: interaction base class. abstract.
	  needs to be activated with the Trigger() function first
	  before it can do anything in the update loop

*/

class InteractionBaseScript : public ScriptComponent
{
protected:
	bool m_bIsTriggered;

	// use these values if you need them.
	float m_fTimeElapsed; // counting from trigger
	float m_fMaximumTimeElapsed; // counting from trigger
public:
	InteractionBaseScript();
	virtual ~InteractionBaseScript();

	virtual void Update(double dt) = 0;
	virtual void Trigger(ComponentBase * player) = 0;
	virtual Component* Clone() = 0;

	void SetMaxElapsedTime(float maxtime);
	bool IsAlreadyTriggered();
};