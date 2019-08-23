#pragma once
#include "ScriptComponent.h"
#include "StopWatch.h"
class BossSpawnerScript :
	public ScriptComponent
{
private:
	StopWatch s;
	int m_iCurrentBoss;
	float m_fCurrentInterval;
	GameObject* m_Boss[3];
	float m_fSpawnIntervals[3];
public:
	BossSpawnerScript(GameObject* a, GameObject* b, GameObject* c);
	virtual ~BossSpawnerScript();
	virtual Component* Clone() { return new BossSpawnerScript(*this); };

	virtual void Start();
	virtual void Update(double dt) override;
	float GetPercentageDone();
};
