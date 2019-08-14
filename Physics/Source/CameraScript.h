#pragma once
#include "ScriptComponent.h"
/********************************************************************************/
/*!
\author Hao Cheng
\brief
Script to control camera movements
/*!
/********************************************************************************/
#define CAMERA_DISTANCE 10
class CameraScript :
	public ScriptComponent
{
private:
	GameObject* m_vTarget;
	static Vector3 m_vOffset;			///< represets offset of camera to player
	static Vector3 m_vRotateOffset;	///< represent current corner its supopsed to be rotated towards
	bool m_bRotating;
	static Vector3 m_vFront;				///<	Front dir of world
	static Vector3 m_vRight;				///<	Right dir of world
	//----------------------------------
	void Rotate();
public:
	CameraScript(GameObject* vTarget);
	virtual ~CameraScript();

	virtual ComponentBase* Clone() { return new CameraScript(*this); };
	virtual void Start() override;
	virtual void Update(double d) override;

	static Vector3 GetFront();
	static Vector3 GetRight();
	static Vector3 GetOffset();
	static Vector3 GetRotateOffset();
};
