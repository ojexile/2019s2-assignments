#include "ReticleScript.h"

#include "InputManager.h"
#include "Application.h"
#include "CameraScript.h"
#include "Utility.h"
#include "RenderingManager.h"
#include "Mtx44.h"
#include "ChunkData.h"
#include  "ChunkCollider.h"
ReticleScript::ReticleScript(ChunkData* chunk)
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
	Vector3 Dir = RenderingManager::MouseWorldDir();
	Vector3 StartPos = GetCameraGO()->TRANS->GetPosition();
	float Offset = 1.73205f; // diag of cube
	for (int i = 0; i < 100; ++i)
	{
		Vector3 Pos = StartPos + Offset * Dir * i;
		if (m_Chunk->IsSolid(Pos))
		{
			TRANS->SetPosition(Pos - Offset * Dir);
			CHENG_LOG("", "Collide Chunk");
			break;
		}
	}
}