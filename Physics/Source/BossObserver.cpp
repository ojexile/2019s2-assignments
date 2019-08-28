#include "BossObserver.h"
#include "BossObserverCom.h"
#include "BossSpawnerScript.h"
#include "SceneManager.h"
#include "MainMenu.h"
BossObserver::BossObserver()
{
	m_iNumBoss = 0;
}

BossObserver::~BossObserver()
{
}

void BossObserver::Notify(ComponentBase * com, std::string msg, std::vector<GameObject*>* OBComList)
{
	if (msg == "BossDied")
	{
		++m_iNumBoss;
		if (m_iNumBoss >= 3)
		{
			SceneManager::GetInstance()->ChangeScene(new MainMenu);
		}
	}
	if (msg == "PlayerIdle")
	{
		for (GameObject* go : *OBComList)
		{
			BossObserverCom* ob = go->GetComponent<BossObserverCom>(true);
			if (!ob)
				continue;
			BossSpawnerScript* bss = ob->GetComponent<BossSpawnerScript>();
			bss->SetSpawnRate(2.f);
			bss->SetState(BossSpawnerScript::eFOUND);
		}
	}
	if (msg == "PlayerNotIdle")
	{
		for (GameObject* go : *OBComList)
		{
			BossObserverCom* ob = go->GetComponent<BossObserverCom>(true);
			if (!ob)
				continue;
			BossSpawnerScript* bss = ob->GetComponent<BossSpawnerScript>();
			bss->SetSpawnRate(1.f);
			bss->SetState(BossSpawnerScript::eSEARCHING);
		}
	}
}