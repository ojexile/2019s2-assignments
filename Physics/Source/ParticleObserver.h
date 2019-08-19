#pragma once
#include "ObserverBase.h"
class ParticleObserver :
	public ObserverBase
{
public:
	ParticleObserver();
	virtual ~ParticleObserver();

	virtual void Notify(ComponentBase* com, std::string msg, std::vector<GameObject*>* OBComList);
};
