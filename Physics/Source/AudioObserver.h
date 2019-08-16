#pragma once
#include "ObserverBase.h"
#include "ComponentBase.h"
class AudioObserver :
	public ObserverBase
{
public:
	AudioObserver();
	virtual ~AudioObserver();

	virtual void Notify(ComponentBase* com, std::string msg);
};

