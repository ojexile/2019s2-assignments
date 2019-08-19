#pragma once
#include "ScriptComponent.h"

/*
author: lorenzo yanga
desc: just an identifier for now to discriminate in the observer
*/

class SpawnLootScript : public ScriptComponent
{
public:
	SpawnLootScript();
	~SpawnLootScript();

	virtual Component* Clone() { return new SpawnLootScript(*this); }
};
