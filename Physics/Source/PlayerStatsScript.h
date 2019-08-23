#pragma once
#include "ScriptComponent.h"
/********************************************************************************/
/*!
\author Hao Cheng
\brief
Hold and update UI display for stats
/*!
/********************************************************************************/
class PlayerStatsScript :
	public ScriptComponent
{
private:
	int m_iMaxMag;
	int m_iMag;
	//
	GameObject* m_Player;
	GameObject* m_Stamina;
	GameObject* m_Health;
	GameObject* m_Gun;
	GameObject* m_BulletUIRef;
	GameObject* m_BossSpawner;
	GameObject* m_BossSpawnerUI;

	std::vector<GameObject*> m_BulletList;
	//
	void InitBulletUI();
	void UpdateBulletUI();
public:
	PlayerStatsScript(GameObject* Player, GameObject* Stamina,
		GameObject* Health, GameObject* Gun,
		GameObject* BulletRef,
		GameObject* BossSpawner,
		GameObject* BossSpawnerUI);
	virtual ~PlayerStatsScript();
	virtual Component* Clone() { return new PlayerStatsScript(*this); };
	virtual void Update(double dt) override;
	virtual void Start() override;
};
