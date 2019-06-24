#pragma once
#include "ComponentBase.h"
#include "Vector3.h"
class TransformComponent :
	public ComponentBase
{
private:
	Vector3 m_vPosition;
	Vector3 m_vScale;
	Vector3 m_vRotateAxis;
	float m_fdegrees;

public:
	TransformComponent();
	TransformComponent(Vector3);
	virtual ~TransformComponent();

	virtual void Update(double dt) override;

	void setScale(float, float, float);
	void setRotation(float, int, int, int);
	void setPosition(float translateX = 0, float translateY = 0, float translateZ = 0);
	void setPosition(Vector3);

	void translateObject(float translateX = 0, float translateY = 0, float translateZ = 0);
	void translateObject(Vector3);

	Vector3 GetPosition();
	Vector3 GetRotation();
	Vector3 GetScale();
	float GetDegrees();


};

