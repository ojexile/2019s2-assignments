#include "ParticleObserver.h"
#include "SceneManager.h"
#include "ComponentMacros.h"
#include "EntityScript.h"
#include "DebrisSpawningScript.h"
#include "AdvancedParticleSpawnerScript.h"
#include "DestructibleEntityScript.h"

ParticleObserver::ParticleObserver()
{
}

ParticleObserver::~ParticleObserver()
{
}

void ParticleObserver::Notify(ComponentBase * com, std::string msg, std::vector<GameObject*>* OBComList)
{
	LZ_LOG(msg);

 	if (msg == "EntityDied")
	{
		LZ_LOG(msg);
	}
	else if (msg == "DestructibleEntityDied")
	{
		LZ_LOG(msg);
		com->GetComponent<DestructibleEntityScript>()->DestroySelf();
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
	else if (msg == "Jump")
	{
		LZ_LOG(msg);
		AdvancedParticleSpawnerScript * script = com->GetComponent<AdvancedParticleSpawnerScript>();
		if (script)
		{
			script->Trigger();
			script->ResetTrigger();
		}
	}
	
}