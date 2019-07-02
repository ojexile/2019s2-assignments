#pragma once
#include "ScriptComponent.h"
#include "CameraComponent.h"
#include "PlayerState.h"
#include "StandingState.h"
class ChengPlayerScript : public ScriptComponent
{
	friend class PlayerState;
private:

private:
	PlayerState* m_CurrentState;
	float m_fMovementSpeed;
public:
	ChengPlayerScript();
	~ChengPlayerScript();

	void Update(double dt) override;
	virtual void Start() override;

	void SetMovementSpeed(float f);
};
