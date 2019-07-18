#pragma once
#include "ScriptComponent.h"
#include "CameraComponent.h"
#include "PlayerState.h"
#include "StandingState.h"
class ChengPlayerScript : public ScriptComponent
{
public:
	enum eSTONES
	{
		NONE,
		SOUL,
		REALITY,
		SPACE,
		POWER,
		TIME,
		MIND,
		TOTAL,
	};
	friend class PlayerState;
private:
	PlayerState* m_CurrentState;
	float m_fMovementSpeed;
	GameObject* m_Gun;
	GameObject* m_CrossHair;
	GameObject* m_Gaunt;
	GameObject* m_Repel;
	bool m_bState;
	bool m_bGaunt;
	eSTONES m_eStone;

	float m_fStartRepel;
	float m_fRepelDuration;
public:
	ChengPlayerScript(GameObject* Gun, GameObject* cross, GameObject* gaunt, GameObject* repel);
	~ChengPlayerScript();
	virtual ComponentBase* Clone()
	{
		return new ChengPlayerScript(*this);
	}

	void Update(double dt) override;
	virtual void Start() override;

	void SetMovementSpeed(float f);
};
