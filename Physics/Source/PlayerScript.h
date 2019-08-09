#pragma once
#include "ScriptComponent.h"
#include "CameraComponent.h"
#include "PlayerState.h"
#include "StandingState.h"
#include "Light.h"
class PlayerScript : public ScriptComponent
{
	friend class PlayerState;
private:
	PlayerState* m_CurrentState;
	float m_fMovementSpeed;
	float m_fAccel;
	float m_fJumpForce;
	bool m_bFirstPerson;

	float m_fHealth;

	// Functions
	// Switch view
	void SwitchView();
	void SetTopDownPos();
	void UpdateMovement(double dt);
public:
	PlayerScript();
	~PlayerScript();
	virtual ComponentBase* Clone()
	{
		return new PlayerScript(*this);
	}

	void Update(double dt) override;
	virtual void Start() override;
	void SetMovementSpeed(float f, float accel);
};
