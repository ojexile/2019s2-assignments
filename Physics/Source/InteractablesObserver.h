#pragma once
#include "ObserverBase.h"
class InteractablesObserver :
	public ObserverBase
{
public:
	InteractablesObserver();
	virtual ~InteractablesObserver();

	virtual void Notify(Component* com, std::string msg, std::vector<GameObject*>* OBComList) override;
};
