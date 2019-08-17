#pragma once
#include "ComponentBase.h"
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
class ScriptComponent : public ComponentBase
{
protected:
	GameObject* Instantiate(const GameObject* goRef, Vector3 pos, Vector3 vScal, Vector3 vRot, float fAngle, std::string sLayer = "Default") const;
	GameObject* Instantiate(const GameObject* goRef, Vector3 pos, Vector3 vScal, std::string sLayer = "Default", bool bIsChild = false) const;
	GameObject* Instantiate(const GameObject* goRef, Vector3 pos, std::string sLayer = "Default") const;
	GameObject* Instantiate(const GameObject* goRef, std::string sLayer = "Default") const;
	void Destroy(GameObject* go);
	void DestroySelf();
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
	virtual ComponentBase* Clone() = 0;
};
