#pragma once
#include <vector>
#include "ObserverBase.h"
#include "ComponentBase.h"
#include "Singleton.h"
class GenericSubject : public Singleton<GenericSubject>
{
private:
	std::vector<ObserverBase*> m_List;
public:
	GenericSubject();
	~GenericSubject();

	void Notify(ComponentBase* com, std::string msg);
};

