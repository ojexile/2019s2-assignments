#include "BlackholeScript.h"
#include "SceneManager.h"
#include <vector>
#include "GameObject.h"
#include "Rigidbody.h"
#include "EntityScript.h"
#define G_CONSTANT 200.f
BlackholeScript::BlackholeScript(float fMass, float fMinDist)
	: m_fMass(fMass)
	, m_fMinDist(fMinDist)
{
}

BlackholeScript::~BlackholeScript()
{
}
void BlackholeScript::Update(double dt)
{
	if (!this->IsActive())
		return;

	GameObjectManager* GOM = SceneManager::GetInstance()->GetScene()->GetGameObjectManager();
	std::vector<GameObject*>* GOList = GOM->GetLayerList()->at("Default")->GetGOList();
	Vector3 pos1 = GetComponent<TransformComponent>()->GetPosition();

	for (unsigned i = 0; i < GOList->size(); ++i)
	{
		GameObject* go = GOList->at(i);
		bool bSkip = false;
		for (GameObject* ig : m_List)
		{
			if (go == ig)
			{
				bSkip = true;
				break;
			}
		}
		if (bSkip)
			continue;

		// only affects rigid bodies
		Rigidbody* rigid = go->GetComponent<Rigidbody>(true);
		if (!rigid)
			continue;
		
		// only affects balls
		if (rigid->GetType() != Rigidbody::BALL)
			continue;

		Vector3 pos2 = go->GetComponent<TransformComponent>()->GetPosition();
		if ((pos1 - pos2).IsZero())
			continue;
		
		float dist = (pos1 - pos2).Length();
		
		if (dist > m_fMinDist)
			continue;
		
		float dmgDist = m_fMinDist / 2;
		int dmg = 10;
		float fForceAttract = G_CONSTANT * (m_fMass * rigid->GetMass()) / (dist);
		
		if (go == SceneManager::GetInstance()->GetScene()->GetPlayer())
		{
			if (dist <= dmgDist)
			{
				go->GetComponent<EntityScript>()->Damage(dmg);
				Vector3 Up(0, 1, 0);
				rigid->AddForce(Up * -fForceAttract * 400);
				Vector3 force = (fForceAttract) * (pos1 - pos2).Normalize();
				rigid->AddForce(force * 100);
			}
		}
		try
		{
			Vector3 force = (fForceAttract) * (pos1 - pos2).Normalize();
			rigid->AddForce(force);
		}
		catch (std::exception e)
		{
		}
	}
}

void BlackholeScript::SetIgnoreList(std::vector<GameObject*> list)
{
	m_List = list;
}