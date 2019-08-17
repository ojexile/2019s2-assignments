#pragma once
#include <string>
#include "ComponentBase.h"
#include "GameObject.h"
class ObserverBase
{
	friend class GenericSubject;
private:
	bool m_bActive;
public:
	ObserverBase();
	~ObserverBase();

	virtual void Notify(ComponentBase* com, std::string msg, std::vector<GameObject*>* OBComList) = 0;
};
