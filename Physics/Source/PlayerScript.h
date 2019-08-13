#pragma once
#include "EntityScript.h"
#include "CameraComponent.h"
#include "PlayerState.h"
#include "StandingState.h"
#include "Light.h"
class PlayerScript : public EntityScript
{
	friend class PlayerState;
private:
	PlayerState* m_CurrentState;

	float m_fJumpForce;
	bool m_bFirstPerson;

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
};
