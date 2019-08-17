#pragma once
#include "ObserverComponent.h"
class InteractableObCom :
	public ObserverComponent
{
public:
	InteractableObCom();
	virtual ~InteractableObCom();
	virtual Component* Clone() { return new InteractableObCom(*this); };
	virtual void Notify(Component* com, std::string msg);
};
