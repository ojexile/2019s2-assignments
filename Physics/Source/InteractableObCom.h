#pragma once
#include "ObserverComponent.h"
class InteractableObCom :
	public ObserverComponent
{
public:
	InteractableObCom();
	virtual ~InteractableObCom();
	virtual ComponentBase* Clone() { return new InteractableObCom(*this); };
	virtual void Notify(ComponentBase* com, std::string msg);
};
