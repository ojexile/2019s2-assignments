#ifndef CAMERA_H
#define CAMERA_H

#include "Vector3.h"

class Camera
{
	friend class CameraComponent;
	friend class RenderingManager;
private:
	Vector3 m_vTarget;
	Vector3 m_vDir;
	Vector3 m_vUp;

	float m_fLastX;
	float m_fLastY;
	bool m_bIsFirstMouseMove;
	float m_fCamSpeed;

	float m_fPitch;
	float m_fYaw;

	void UpdateFirstPersonView(double dt, Vector3 vPos);
public:

	Camera();
	~Camera();
	virtual void Init(const Vector3& target, const Vector3& up);
	virtual void Reset();
	virtual void Update(double dt);
	void UpdateYawPitchMouse(float xpos, float ypos);

	// Getters
	Vector3* GetTarget();
	Vector3* GetUp();
	Vector3* GetDir();
};

#endif