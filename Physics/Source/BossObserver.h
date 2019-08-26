#pragma once
#include "ObserverBase.h"
class BossObserver :
	public ObserverBase
{
public:
	BossObserver();
	virtual ~BossObserver();

	virtual void Notify(ComponentBase* com, std::string msg, std::vector<GameObject*>* OBComList);
};
