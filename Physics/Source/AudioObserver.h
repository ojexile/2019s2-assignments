#pragma once
#include "ObserverBase.h"
#include "ComponentBase.h"
class AudioObserver :
	public ObserverBase
{
public:
	AudioObserver();
	virtual ~AudioObserver();

	virtual void Notify(Component* com, std::string msg, std::vector<GameObject*>* OBComList) override;
};