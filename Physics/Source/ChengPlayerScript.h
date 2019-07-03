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
public:
	ChengPlayerScript(GameObject* Gun);
	~ChengPlayerScript();
	virtual ComponentBase* Clone()
	{
		return new ChengPlayerScript(*this);
	}

	void Update(double dt) override;
	virtual void Start() override;

	void SetMovementSpeed(float f);
};
