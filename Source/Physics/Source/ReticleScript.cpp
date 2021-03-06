#include "ReticleScript.h"

#include "InputManager.h"
#include "Application.h"
#include "CameraScript.h"
#include "Utility.h"
#include "RenderingManager.h"
#include "Mtx44.h"
#include "ChunkData.h"
#include  "ChunkCollider.h"
#include "GameObjectManager.h"
#include "WeaponPartScript.h"

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
	//float UD = InputManager::GetInstance()->GetInputStrength("ReticleUpDown");
	//float LR = InputManager::GetInstance()->GetInputStrength("ReticleLeftRight");
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
	GameObjectManager* GOM = SceneManager::GetInstance()->GetScene()->GetGameObjectManager();
	// get chunks
	std::vector<GameObject*> ChunkList;
	float fDist = 64 * 64;
	std::vector<GameObject*>* GOList = GOM->GetLayerList()->at("Default")->GetGOList();
	GameObject* PartFound = nullptr;
	float PartDistSqrd = -1;
	for (unsigned i = 0; i < GOList->size(); ++i)
	{
		GameObject* go = GOList->at(i);
		ChunkCollider* chunkcol = go->GetComponent<ChunkCollider>(true);
		if (chunkcol)
		{
			Vector3 ChunkXZ = chunkcol->TRANS->GetPosition();
			ChunkXZ.y = 0;
			Vector3 PosXZ = GetPosition();
			PosXZ.y = 0;
			// dist check
			if ((ChunkXZ - PosXZ).LengthSquared() < fDist)
			{
				ChunkList.push_back(go);
			}
			continue;
		}
		WeaponPartScript* wp = go->GetComponent<WeaponPartScript>(true);
		if (wp)
		{
			float maxPartDist = 2;
			Vector3 PartPos = wp->TRANS->GetPosition();
			Vector3 Pos = GetPosition();
			// dist check
			float fCurrentPartDistSqrd = (Pos - PartPos).LengthSquared();
			if (fCurrentPartDistSqrd < maxPartDist)
			{
				if (!PartFound)
				{
					PartFound = go;
					PartDistSqrd = fCurrentPartDistSqrd;
				}
				else if (fCurrentPartDistSqrd < PartDistSqrd)
				{
					PartFound = go;
					PartDistSqrd = fCurrentPartDistSqrd;
				}
			}
			continue;
		}
	}
	if (PartFound)
	{
		GetChild(0)->SetActive(PartFound);
		GetChild(0)->RENDER->SetText(PartFound->GetComponent<WeaponPartScript>()->GetName());
	}
	else
	{
		GetChild(0)->SetActive(false);
	}
	Vector3 Dir = RenderingManager::MouseWorldDir();
	Vector3 StartPos = GetCameraGO()->TRANS->GetPosition();
	float Offset = 1.73205f; // diag of cube
	int SmallestDist = 101;
	ChunkData* CollidedChunk = nullptr;
	GameObject* CollideGo = nullptr;
	Vector3 CollidePos;
	for (unsigned j = 0; j < ChunkList.size(); ++j)
	{
		GameObject* go = ChunkList.at(j);
		ChunkData* chunk = go->GetComponent<ChunkCollider>()->GetChunk();
		for (int i = 0; i < 100; ++i)
		{
			Vector3 Pos = StartPos + Offset * Dir * (float)i;
			if (chunk->IsSolid(Pos - go->TRANS->GetPosition()))
			{
				if (i < SmallestDist)
				{
					CollidePos = Pos;
					CollidedChunk = chunk;
					SmallestDist = i;
					CollideGo = go;
				}
			}
		}
	}
	if (SmallestDist < 101)
	{
		float fOffset = 0.1f;
		for (int i = 0; i < 20; ++i)
		{
			Vector3 Pos = CollidePos + fOffset * -Dir * (float)i;
			if (!CollidedChunk->IsSolid(Pos - CollideGo->TRANS->GetPosition()))
			{
				TRANS->SetPosition(Pos);
				break;
			}
		}
	}
}