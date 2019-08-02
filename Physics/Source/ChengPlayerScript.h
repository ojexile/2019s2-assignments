#pragma once
#include "ScriptComponent.h"
#include "CameraComponent.h"
#include "PlayerState.h"
#include "StandingState.h"
#include "Light.h"
class ChengPlayerScript : public ScriptComponent
{
	friend class PlayerState;
private:
	PlayerState* m_CurrentState;
	float m_fMovementSpeed;
	std::vector<GameObject*> m_Guns;
	GameObject* m_CurrentGun;
	GameObject* m_CrossHair;
	GameObject* m_Gaunt;
	bool m_bState;

	Light* m_Light;

	// Functions
	// Switch view
	void SwitchView();
	void UpdateMovement(double dt);
	void UpdateGauntlet();
	void UpdateTilt();
	void UpdateConstrain();
public:
	ChengPlayerScript(GameObject* Gun, GameObject* cross, GameObject* gaunt);
	~ChengPlayerScript();
	virtual ComponentBase* Clone()
	{
		return new ChengPlayerScript(*this);
	}

	void Update(double dt) override;
	virtual void Start() override;

	void SetDefaultCamPos();
	void SetMovementSpeed(float f);
};
