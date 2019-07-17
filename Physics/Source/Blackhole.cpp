#include "Blackhole.h"
#include "SceneManager.h"
#include <vector>
#include "GameObject.h"
#include "ChengRigidbody.h"
#define G_CONSTANT 100.f
Blackhole::Blackhole(float fMass, float fMinDist)
	: m_fMass(fMass)
	, m_fMinDist(fMinDist)
{
}

Blackhole::~Blackhole()
{
}
void Blackhole::Update(double dt)
{
	GameObjectManager* GOM = SceneManager::GetInstance()->GetScene()->GetGameObjectManager();
	std::vector<GameObject*>* GOList = GOM->GetLayerList()->at("Default")->GetGOList();
	Vector3 pos1 = GetComponent<TransformComponent>()->GetPosition();
	for (unsigned i = 0; i < GOList->size(); ++i)
	{
		GameObject* go = GOList->at(i);
		// only affects rigid bodies
		ChengRigidbody* rigid = go->GetComponent<ChengRigidbody>();
		if (!rigid)
			continue;
		// only affects balls
		if (rigid->GetType() != ChengRigidbody::BALL)
			continue;
		Vector3 pos2 = go->GetComponent<TransformComponent>()->GetPosition();

		float dist = (pos1 - pos2).Length();
		if ((pos1 - pos2).IsZero())
			continue;
		if (dist > m_fMinDist)
			continue;
		float fForceAttract = G_CONSTANT * (m_fMass * rigid->GetMass()) / (dist);
		try
		{
			Vector3 force = (fForceAttract) * (pos1 - pos2).Normalize() * (float)dt;
			rigid->IncrementForce(force);
		}
		catch (std::exception e)
		{
		}
	}
}