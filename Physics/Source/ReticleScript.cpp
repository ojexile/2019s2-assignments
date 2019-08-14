#include "ReticleScript.h"

#include "InputManager.h"
#include "Application.h"
#include "CameraScript.h"
ReticleScript::ReticleScript()
{
}

ReticleScript::~ReticleScript()
{
}
void ReticleScript::Start()
{
	GetTransform()->SetRelativePosition(-CameraScript::GetOffset());
}
void ReticleScript::Update(double dt)
{
	float UD = InputManager::GetInstance()->GetInputStrength("ReticleUpDown");
	float LR = InputManager::GetInstance()->GetInputStrength("ReticleLeftRight");
	Vector3 Front = CameraScript::GetFront();
	Vector3 Right = CameraScript::GetRight();
	m_vOffset += (Front  * UD);
	m_vOffset += (Right  * LR);
	GetTransform()->SetRelativePosition(m_vOffset + -CameraScript::GetOffset());
	CHENG_LOG("", VectorToString(GetTransform()->GetScale()));
	// CHENG_LOG("Reticle Pos: ", VectorToString(GetPosition()));
	///Screen space update------------------------------------------------------------------------------------
	//Vector3 vOrigin = { 1920 / 2, 1080 / 2 };

	//float fPlanDist = 10;

	//double x, y;
	//Application::GetCursorPos(&x, &y);
	//x = 1920 / 2;
	//y = 1080 / 2;
	//Vector3 ScreenPos((float)x, (float)y, -fPlanDist);

	//Vector3 vDir = ScreenPos - vOrigin;
	//Mtx44 rot;
	//rot.SetToRotation(4fOffset, 1, 1, 1);
	//vDir = rot * vDir;

	//Vector3 CamPos = GetCameraGO()->TRANS->GetPosition();

	//Vector3 vWorldSpace = CamPos + vDir.Normalized() * 100;

	//GetTransform()->SetPosition(vWorldSpace);
}