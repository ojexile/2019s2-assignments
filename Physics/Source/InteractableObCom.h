#pragma once
#include "ObserverComponent.h"
#include <string>

class InteractableObCom :
	public ObserverComponent
{
private:
	//std::string m_sNotifyMessage;
public:
	InteractableObCom();
	virtual ~InteractableObCom();
	virtual ComponentBase* Clone() { return new InteractableObCom(*this); };
	virtual void Notify(ComponentBase* com, std::string msg);
};
