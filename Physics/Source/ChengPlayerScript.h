#pragma once
#include "ScriptComponent.h"
#include "CameraComponent.h"
#include "PlayerState.h"
#include "StandingState.h"
class ChengPlayerScript : public ScriptComponent
{
	friend class PlayerState;
private:
	PlayerState* m_CurrentState;
	float m_fMovementSpeed;
	GameObject* m_Gun;
	GameObject* m_CrossHair;
	bool m_bState;
public:
	ChengPlayerScript(GameObject* Gun, GameObject* cross);
	~ChengPlayerScript();
	virtual ComponentBase* Clone()
	{
		return new ChengPlayerScript(*this);
	}

	void Update(double dt) override;
	virtual void Start() override;

	void SetMovementSpeed(float f);
};
