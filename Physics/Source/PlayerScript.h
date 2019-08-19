#pragma once
#include "EntityScript.h"
#include "CameraComponent.h"
#include "Light.h"
#include "Behaviour.h"
class PlayerScript : public EntityScript
{
private:
	GameObject* m_Reticle;
	GameObject* m_Gun;
	GameObject* m_Grenade;
	float m_fJumpForce;
	bool m_bCanJump;
	int m_iNumberOfGrenades;

	// Functions
	void UpdateMovement(double dt);
public:
	void Dash();
	PlayerScript(Behaviour* beh, GameObject* Reticle, GameObject* gun, GameObject* grenade);
	~PlayerScript();
	virtual Component* Clone()
	{
		return new PlayerScript(*this);
	}
	void SetCanJump(bool b);
	void Update(double dt) override;
	virtual void Start() override;
	virtual void Collide(GameObject*) override;
};
