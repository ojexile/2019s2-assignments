#pragma once
#include "ObserverBase.h"
class InteractablesObserver :
	public ObserverBase
{
public:
	InteractablesObserver();
	virtual ~InteractablesObserver();

	virtual void Notify(ComponentBase* com, std::string msg, std::vector<GameObject*>* OBComList) override;
};
