#pragma once
#include "EntityScript.h"
#include "CameraComponent.h"
#include "PlayerState.h"
#include "StandingState.h"
#include "Light.h"
class PlayerScript : public EntityScript
{
	friend class PlayerState;
	friend class StandingState;
private:
	PlayerState* m_CurrentState;
	GameObject* m_Reticle;
	GameObject* m_Gun;
	GameObject* m_Grenade;
	float m_fJumpForce;
	int m_iNumberOfGrenades;

	// Functions
	void UpdateMovement(double dt);
public:
	void Dash();
	PlayerScript(GameObject* Reticle, GameObject* gun, GameObject* grenade);
	~PlayerScript();
	virtual ComponentBase* Clone()
	{
		return new PlayerScript(*this);
	}

	void Update(double dt) override;
	void ThrowGrenade(void);
	virtual void Start() override;
	virtual void Collide(GameObject*) override;
};
