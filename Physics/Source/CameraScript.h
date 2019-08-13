#pragma once
#include "ScriptComponent.h"
/********************************************************************************/
/*!
\author Hao Cheng
\brief
Script to control camera movements
/*!
/********************************************************************************/
#define CAMERA_DISTANCE 50
class CameraScript :
	public ScriptComponent
{
private:
	GameObject* m_vTarget;
	Vector3 m_vOffset;			///< represets offset of camera to player
	Vector3 m_vRotateOffset;	///< represent current corner its supopsed to be rotated towards
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
