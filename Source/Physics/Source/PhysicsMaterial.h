#pragma once
class PhysicsMaterial
{
private:
	float m_fFriction;
	float m_fBounciness;
public:
	PhysicsMaterial();
	PhysicsMaterial(float, float);
	~PhysicsMaterial();

	void SetMat(float fric, float bounce);
	float GetFriction();
	float GetBounce();
};
