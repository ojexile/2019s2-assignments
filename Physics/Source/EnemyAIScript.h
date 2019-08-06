#pragma once
#include "ScriptComponent.h"
class EnemyAIScript :
	public ScriptComponent
{
private:
	float m_fHealth;
	GameObject* m_Player;
	void Movement();
public:
	EnemyAIScript(GameObject* player);
	virtual ~EnemyAIScript();
	virtual ComponentBase* Clone() { return new EnemyAIScript(*this); };
	virtual void Update(double dt);
	void Damage(float i);
};
