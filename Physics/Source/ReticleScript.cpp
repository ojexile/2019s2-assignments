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
	GetTransform()->SetRelativePosition(-CAMERA_DISTANCE, -CAMERA_DISTANCE, -CAMERA_DISTANCE);
	GetTransform()->SetRelativePosition(-CAMERA_DISTANCE, -CAMERA_DISTANCE + 16, -CAMERA_DISTANCE); // overwriting  y pos as terrain coll has not been set up
}
void ReticleScript::Update(double dt)
{
	float UD = InputManager::GetInstance()->GetInputStrength("ReticleUpDown");
	float LR = InputManager::GetInstance()->GetInputStrength("ReticleLeftRight");
	Vector3 Front(-1, 0, -1);
	Vector3 Right(1, 0, -1);
	GetTransform()->TranslateRelative(Front  * UD);
	GetTransform()->TranslateRelative(Right  * LR);
	CHENG_LOG("Reticle Pos: ", VectorToString(GetPosition()));
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
	//rot.SetToRotation(45, 1, 1, 1);
	//vDir = rot * vDir;

	//Vector3 CamPos = GetCameraGO()->TRANS->GetPosition();

	//Vector3 vWorldSpace = CamPos + vDir.Normalized() * 100;

	//GetTransform()->SetPosition(vWorldSpace);
}