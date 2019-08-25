#include "BossObserver.h"
#include "BossObserverCom.h"
#include "BossSpawnerScript.h"
BossObserver::BossObserver()
{
}

BossObserver::~BossObserver()
{
}

void BossObserver::Notify(ComponentBase * com, std::string msg, std::vector<GameObject*>* OBComList)
{
	if (msg == "PlayerIdle")
	{
		for (GameObject* go : *OBComList)
		{
			BossObserverCom* ob = go->GetComponent<BossObserverCom>(true);
			if (!ob)
				continue;
			BossSpawnerScript* bss = ob->GetComponent<BossSpawnerScript>();
			bss->SetSpawnRate(2.f);
			bss->SetState("Searching for player...DO NOT IDLE.");
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
			bss->SetState("Found player... STAY ON THE MOVE.");
		}
	}
}