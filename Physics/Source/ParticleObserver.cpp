#include "ParticleObserver.h"
#include "SceneManager.h"
#include "ComponentMacros.h"
#include "EntityScript.h"
#include "DebrisSpawningScript.h"

ParticleObserver::ParticleObserver()
{
}

ParticleObserver::~ParticleObserver()
{
}

void ParticleObserver::Notify(ComponentBase * com, std::string msg, std::vector<GameObject*>* OBComList)
{
	
	if (msg == "EntityDied")
	{
		LZ_LOG(msg);
	}
	else if (msg == "DestructiveEntityDied")
	{
		LZ_LOG(msg);
	}
	else if (msg == "RockDied")
	{
		LZ_LOG(msg);
		DebrisSpawningScript* debrisscript = com->GetComponent<DebrisSpawningScript>();
		if (debrisscript)
		{
			debrisscript->Trigger();
			//debrisscript->DestroySelf();
		}
		// spawn particle spawner here too
	}
	
}