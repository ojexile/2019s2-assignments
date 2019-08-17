#include "ParticleObserver.h"
#include "SceneManager.h"
#include "ComponentMacros.h"
#include "EntityScript.h"

ParticleObserver::ParticleObserver()
{
}

ParticleObserver::~ParticleObserver()
{
}

void ParticleObserver::Notify(Component * com, std::string msg, std::vector<GameObject*>* OBComList)
{
	if (msg == "EntityDied")
	{
		LZ_LOG("EntityDied");
		/*auto scene = SceneManager::GetInstance()->GetScene();
		com->GetComponent<EntityScript>()->Instantiate(
		scene->GetGameObjectManager()->AddGameObject(scene->GetGO("particlespawnerdestroy")
		));*/

	}
}