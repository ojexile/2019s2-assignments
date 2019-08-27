#pragma once
#include "ScriptComponent.h"

/*
author: lorenzo yanga
desc: just an identifier for now to discriminate in the observer, also a public boolean that 
*/

class SpawnLootScript : public ScriptComponent
{
private:
public:

	bool m_isActivated;

	SpawnLootScript();
	~SpawnLootScript();

	virtual Component* Clone() { return new SpawnLootScript(*this); }

};
