#pragma once
#include "ScriptComponent.h"
#include "CameraComponent.h"
class PlayerScript : public ScriptComponent
{
private:
	Vector3* m_vCameraFront;
	Vector3* m_vCameraUp;
	GameObject* m_GORef;
public:
	PlayerScript(GameObject* goRef);
	~PlayerScript();
	virtual ComponentBase* Clone()
	{
		return new PlayerScript(*this);
	}

	void Update(double dt) override;
	virtual void Start() override;
};
