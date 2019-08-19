#pragma once
#include "Component.h"
#include "GameObject.h"
#include <string>
#include "Time.h"
#include "ComponentMacros.h"

#include "LightManager.h"
#include "Camera.h"
#include "GenericSubject.h"
/********************************************************************************/
/*!
\author Hao Cheng
\brief

/*!
/********************************************************************************/
class ScriptComponent : public Component
{
protected:
	// QoL
	Camera* GetCamera();
	GameObject* GetCameraGO();
	LightManager* GetLightManager();
	TransformComponent* GetTransform();
	void Notify(std::string msg);
public:
	ScriptComponent();
	virtual ~ScriptComponent();

	virtual void Update(double dt);
	virtual void Collide(GameObject*);
	virtual Component* Clone() = 0;
};
