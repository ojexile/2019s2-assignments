#pragma once
#include "ScriptComponent.h"
class EnemyAIScript :
	public ScriptComponent
{
private:
	float m_fHealth;
	GameObject* m_Player;
	GameObject* m_Gun;
	void Movement(double dt);
public:
	EnemyAIScript(GameObject* player, GameObject* gun);
	virtual ~EnemyAIScript();
	virtual ComponentBase* Clone() { return new EnemyAIScript(*this); };
	virtual void Update(double dt);
	void Damage(float i);
};
