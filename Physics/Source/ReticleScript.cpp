#include "ReticleScript.h"
#include "Application.h"


ReticleScript::ReticleScript()
{
}


ReticleScript::~ReticleScript()
{
}


void ReticleScript::Update(double dt)
{
	Vector3 vOrigin = {1920/2, 1080/2};

	float fPlanDist = 10;

	double x, y;
	Application::GetCursorPos(&x, &y);
	x = 1920 / 2;
	y = 1080 / 2;
	Vector3 ScreenPos((float)x, (float)y, -fPlanDist);

	Vector3 vDir = ScreenPos - vOrigin;
	Mtx44 rot;
	rot.SetToRotation(45,1, 1, 1);
	vDir = rot * vDir;
	
	Vector3 CamPos = GetCameraGO()->TRANS->GetPosition();

	Vector3 vWorldSpace = CamPos + vDir.Normalized() * 100;

	GetTransform()->SetPosition(vWorldSpace);
}