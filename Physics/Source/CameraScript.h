#pragma once
#include "ScriptComponent.h"
/********************************************************************************/
/*!
\author Hao Cheng
\brief
Script to control camera movements
/*!
/********************************************************************************/
class CameraScript :
	public ScriptComponent
{
private:
	GameObject* m_vTarget;
	Vector3 m_vOffset;
	Vector3 m_vRotateOffset;
	bool m_bRotating;
	//----------------------------------
	void Rotate();
public:
	CameraScript(GameObject* vTarget);
	virtual ~CameraScript();
	virtual ComponentBase* Clone() { return new CameraScript(*this); };
	virtual void Start() override;
	virtual void Update(double d) override;
};

