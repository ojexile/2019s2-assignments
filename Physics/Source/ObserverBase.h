#pragma once
#include <string>
#include "ComponentBase.h"
class ObserverBase
{
	friend class GenericSubject;
private:
	bool m_bActive;
public:
	ObserverBase();
	~ObserverBase();

	virtual void Notify(ComponentBase* go, std::string msg) = 0;
};

