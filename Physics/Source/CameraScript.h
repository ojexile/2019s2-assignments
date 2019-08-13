#pragma once
#include "ScriptComponent.h"
class CameraScript :
	public ScriptComponent
{
private:
	GameObject* m_vTarget;
public:
	CameraScript(GameObject* vTarget);
	virtual ~CameraScript();
	virtual ComponentBase* Clone() { return new CameraScript(*this); };
	virtual void Start() override;
	virtual void Update(double d) override;
};

