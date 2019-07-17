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
	bool m_bState;
	bool m_bGaunt;
	eSTONES m_eStone;
public:
	ChengPlayerScript(GameObject* Gun, GameObject* cross, GameObject* gaunt);
	~ChengPlayerScript();
	virtual ComponentBase* Clone()
	{
		return new ChengPlayerScript(*this);
	}

	void Update(double dt) override;
	virtual void Start() override;

	void SetMovementSpeed(float f);
};
