#pragma once
#include "ScriptComponent.h"
#include <cstdlib>
class ParticleScript :
	public ScriptComponent
{
private:
	const float m_fLifeTime;
	Vector3 m_vSpeed;
	const Vector3 m_vGravity;
	const Vector3 m_vAccel;
	const Vector3 m_vSizeChange;
	const Vector3 m_vRandAxis;
	float m_CurrentDuration;
	bool Started = false;
	const Vector3 m_vSin;
	const Vector3 m_vSinFreq;

	Vector3 m_vCos;
	Vector3 m_vCosFreq;

	//rot
	Vector3 m_vRotateRate;
public:
	ParticleScript(const float fLifeTime, const Vector3 vSpeed,
		const Vector3 vGravity, const Vector3 vAccel,
		const Vector3 vSizeChange
		, const Vector3 vRandAxis, const Vector3 sinamp = { 0,0,0 }, const Vector3 sinfreq = { 0,0,0 });
	virtual ~ParticleScript();
	virtual Component* Clone() { return new ParticleScript(*this); }

	// Cos
	void SetCos(Vector3, Vector3);
	// Rot
	void SetRot(Vector3);
	// virtual void Start();
	virtual void Update(double dt) override;
};
