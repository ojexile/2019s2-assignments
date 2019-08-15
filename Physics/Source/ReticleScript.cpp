#include "ReticleScript.h"

#include "InputManager.h"
#include "Application.h"
#include "CameraScript.h"
#include "Utility.h"
#include "RenderingManager.h"
#include "Mtx44.h"
ReticleScript::ReticleScript(GameObject* chunk)
	:m_Chunk(chunk)
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
	//Vector3 Front = CameraScript::GetFront();
	//Vector3 Right = CameraScript::GetRight();
	//m_vOffset += (Front  * UD);
	//m_vOffset += (Right  * LR);
	//Vector3 TargetPos = m_vOffset + -CameraScript::GetOffset();
	//Vector3 RelPos = Lerp(GetTransform()->GetRelativePosition(), TargetPos, 0.5f);

	//GetTransform()->SetRelativePosition(RelPos);
	//CHENG_LOG("", VectorToString(GetTransform()->GetScale()));
	// CHENG_LOG("Reticle Pos: ", VectorToString(GetPosition()));
	///Screen space update------------------------------------------------------------------------------------
	//if (UD > 0)
	{
		Vector3 Dir = RenderingManager::MouseWorldDir();
		GetTransform()->SetRelativePosition(Dir * 30);
	}
}