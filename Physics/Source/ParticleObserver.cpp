#include "ParticleObserver.h"



ParticleObserver::ParticleObserver()
{
}


ParticleObserver::~ParticleObserver()
{
}

void ParticleObserver::Notify(ComponentBase * com, std::string msg, std::vector<GameObject*>* OBComList)
{
	if(msg == "EntityDied")
	{
		LZ_LOG("EntityDied");
	}
}
