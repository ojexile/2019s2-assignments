#pragma once
#include "EntityScript.h"
#include "CameraComponent.h"
#include "Light.h"
#include "Behaviour.h"
#define IDLE_DIST 16*16
#define IDLE_TIME 3
class PlayerScript : public EntityScript
{
private:
	GameObject* m_Reticle;
	GameObject* m_Gun;
	GameObject* m_Grenade;
	float m_fJumpForce;
	int m_iNumberOfGrenades;
	Vector3 PrevPos;
	StopWatch PlayerIdleTimer;

	// Functions
	void UpdateMovement(double dt);
	void UpdatePrevPos();
public:
	void Dash();
	PlayerScript(Behaviour* beh, GameObject* Reticle, GameObject* gun, GameObject* grenade);
	~PlayerScript();
	virtual Component* Clone()
	{
		return new PlayerScript(*this);
	}
	void Update(double dt) override;
	virtual void Start() override;
	virtual void Collide(GameObject*) override;
};
