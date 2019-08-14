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
	GameObject* m_Reticle;
	GameObject* m_Gun;
	float m_fJumpForce;


	// Functions
	void UpdateMovement(double dt);
public:
	PlayerScript(GameObject* Reticle, GameObject* gun);
	~PlayerScript();
	virtual ComponentBase* Clone()
	{
		return new PlayerScript(*this);
	}

	void Update(double dt) override;
	virtual void Start() override;
	virtual void Collide(GameObject*) override;
};
