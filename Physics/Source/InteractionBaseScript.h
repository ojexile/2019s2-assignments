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
private:
	bool m_bIsTriggered;
	float m_fTimeElapsed; // counting from trigger
	float m_fMaximumTimeElapsed; // counting from trigger
public:
	InteractionBaseScript();
	virtual ~InteractionBaseScript();

	virtual void Update(double dt) = 0;
	virtual void Trigger(GameObject* go1, GameObject * go2) = 0;
	virtual Component* Clone() = 0;
};