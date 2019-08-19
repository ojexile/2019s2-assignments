#pragma once
#include "ComponentBase.h"
#include "Vector3.h"
class TransformComponent :
	public ComponentBase
{
private:
	Vector3 m_vPosition;
	Vector3 m_vQueuedTranslation;
	Vector3 m_vRelativePosition;
	Vector3 m_vScale;
	Vector3 m_vRelativeScale;
	Vector3 m_vRotateAxis;
	Vector3 m_vRelativeRotateAxis;
	int m_iQueuedTranslationCount;
	float m_fDegrees;
	float m_fRelativeDegrees;

public:
	TransformComponent();
	TransformComponent(Vector3);
	virtual ~TransformComponent();
	virtual ComponentBase* Clone()
	{
		return new TransformComponent(*this);
	}

	virtual void Update(double dt);

	void SetScale(float, float, float);
	void SetScale(Vector3);
	void SetRelativeScale(Vector3);
	void SetScale(float);
	void SetRelativeScale(float);
	void ScaleBy(Vector3);
	void SetRotation(float, int, int, int);
	void SetRotation(float, float, float, float);
	void SetRotation(float, Vector3);
	void SetRelativeRotation(float, int, int, int);
	void SetRelativeRotation(float, float, float, float);
	void SetRelativeRotation(float, Vector3);
	void RotateBy(float, Vector3);
	void SetPosition(float translateX = 0, float translateY = 0, float translateZ = 0);
	void SetPosition(Vector3);
	void SetRelativePosition(float translateX = 0, float translateY = 0, float translateZ = 0);
	void SetRelativePosition(Vector3);

	void Translate(float translateX = 0, float translateY = 0, float translateZ = 0);
	void Translate(Vector3);
	void QueueTranslate(Vector3);
	void TranslateRelative(float translateX = 0, float translateY = 0, float translateZ = 0);
	void TranslateRelative(Vector3);

	Vector3 GetPosition();
	Vector3 GetRelativePosition();
	Vector3 GetRotation();
	Vector3 GetRelativeRotation();
	Vector3 GetScale();
	Vector3 GetRelativeScale();
	float GetDegrees();
	float GetRelativeDegrees();
};
