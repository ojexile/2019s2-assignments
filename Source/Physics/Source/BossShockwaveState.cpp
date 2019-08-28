#include "BossShockwaveState.h"
#include "EntityScript.h"
#include "SceneManager.h"
#include "Rigidbody.h"
#include "IdleState.h"
#include "AIStatesList.h"
#include "AIEntityScript.h"

#include "GameObject.h"
#include "GameObjectManager.h"
#include "SceneManager.h"
#include "DataContainer.h"
#include "BlackholeScript.h"
#include <vector>

#define SHOCKWAVE_TIME 4.f
BossShockwaveState::BossShockwaveState()
{
	m_bTriggered = false;
}

BossShockwaveState::~BossShockwaveState()
{
}

State * BossShockwaveState::HandleState(ComponentBase * com)
{
	if (s.GetTime() >= 0.5f && !m_bTriggered)
	{
		// Create shockwave effect
		GameObjectManager* GOM = SceneManager::GetInstance()->GetScene()->GetGameObjectManager();
		float num = 48;
		float angleOffset = 360 / num;
		Vector3 Pos = com->TRANS->GetPosition();
		Pos.y = 17;
		for (int i = 0; i < num; ++i)
		{
			float angle = angleOffset * i;
			GameObject* go = GOM->AddGameObject(DataContainer::GetInstance()->
				GetGameObject("Shockwave"), "NoCollision");
			Vector3 vForce = { cos(angle), 0, sin(angle) };
			vForce *= 130.f;
			go->RIGID->AddForce(vForce);
			go->TRANS->SetPosition(Pos);
			std::vector<GameObject*> list;
			Component* comp = dynamic_cast<Component*>(com);
			list.push_back(comp->GetGO());
			go->GetComponent<BlackholeScript>()->SetIgnoreList(list);
		}
		//
		m_bTriggered = true;
	}

	if (s.Stop()->GetTime() >= SHOCKWAVE_TIME)
		return &AIStatesList::Boss;
	else
		return this;
}

void BossShockwaveState::OnEnter(ComponentBase * com)
{
	m_bTriggered = false;
	com->GetComponent<AIEntityScript>()->SetTarget({ 0, 0, 0 });
	GameObject* ret = dynamic_cast<Component*>(com)->GetChild(0);
	if (ret)
		ret->RENDER->SetColor(1, 0.1f, 1);

	com->GetComponent<EntityScript>()->Jump();
	s.Start();
}

void BossShockwaveState::OnExit(ComponentBase * com)
{
}