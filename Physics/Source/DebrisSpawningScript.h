#pragma once
#include "InteractionBaseScript.h"
#include <vector>
/*
author: lorenzo yanga
desc: trigger script, debris spawning around it will spawn objects is m_vGOtoSpawn and trigger DestroySelf on update.
*/

class DebrisSpawningScript : public ScriptComponent
{
private:
	std::string m_sDebrisName;  
	int m_iMin;
	int m_iMax;
	
	bool m_bTriggered;
public:
	DebrisSpawningScript();
	DebrisSpawningScript(std::string name, int, int );

	~DebrisSpawningScript();
	virtual Component* Clone() { return new DebrisSpawningScript(*this); }

	void SetDebrisName(std::string name);
	void SetMinMax(int, int);
	void Trigger();
};

