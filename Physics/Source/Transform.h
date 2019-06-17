#pragma once
#include "ComponentBase.h"

#include "Vector3.h"

class Transform :
	public ComponentBase
{
private:
	Vector3 m_vPosition;
	Vector3 m_vRotation;
	Vector3 m_vScale;
public:
	Transform();
	virtual ~Transform();

	virtual void Update(double dt) override;
	Vector3 GetPosition();
	Vector3 GetRotation();
	Vector3 GetScale();

	void SetPosition(Vector3 pos);
	void SetPosition(float x = 0, float y = 0, float z = 0);
};
