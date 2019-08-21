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

#define SHOCKWAVE_TIME 2.f
BossShockwaveState::BossShockwaveState()
{
}

BossShockwaveState::~BossShockwaveState()
{
}

State * BossShockwaveState::HandleState(ComponentBase * com)
{
	if (s.Stop()->GetTime() >= SHOCKWAVE_TIME)
		return &AIStatesList::Boss;
	else
		return this;
}

void BossShockwaveState::OnEnter(ComponentBase * com)
{
	com->RENDER->SetColor(1, 0.1f, 0);
	// Create shockwave effect
	GameObjectManager* GOM = SceneManager::GetInstance()->GetScene()->GetGameObjectManager();
	GameObject* go = GOM->AddGameObject(DataContainer::GetInstance()->
		GetGameObject("Shockwave"));
	go->TRANS->SetPosition(com->TRANS->GetPosition());
	std::vector<GameObject*> list;
	Component* comp = dynamic_cast<Component*>(com);
	list.push_back(comp->GetGO());
	go->GetComponent<BlackholeScript>()->SetIgnoreList(list);
	//
	s.Start();
}

void BossShockwaveState::OnExit(ComponentBase * com)
{
}