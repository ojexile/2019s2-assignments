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
	float m_fStamina;
	float m_fHealth;
	float m_fTime;
	//
	GameObject* m_Player;
	GameObject* m_Stamina;
	GameObject* m_Health;
public:
	PlayerStatsScript(GameObject* Player, GameObject* Stamina, GameObject* Health);
	virtual ~PlayerStatsScript();
	virtual ComponentBase* Clone() { return new PlayerStatsScript(*this); };
	virtual void Update(double dt) override;

	void DrainStamina(float f);
	float GetStamina();
};

