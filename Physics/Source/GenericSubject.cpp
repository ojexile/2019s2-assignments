#include "GenericSubject.h"



GenericSubject::GenericSubject()
{
}


GenericSubject::~GenericSubject()
{
}
void GenericSubject::Notify(ComponentBase* com, std::string msg)
{
	for (unsigned i = 0; i < m_List.size(); ++i)
	{
		ObserverBase* ob = m_List.at(i);
		if (!ob->m_bActive)
			continue;
		ob->Notify(com, msg);
	}
}