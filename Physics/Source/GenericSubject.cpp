#include "GenericSubject.h"

GenericSubject::GenericSubject()
{
}

GenericSubject::~GenericSubject()
{
	for (unsigned j = 0; j < m_ObList.size(); ++j)
	{
		ObserverBase* ob = m_ObList.at(j);
		delete ob;
	}
}
void GenericSubject::NotifySubject(ComponentBase* com, std::string msg)
{
	m_Messages.push_back(new Message(com, msg));
	// update observers
}
void GenericSubject::NotifyObservers(std::vector<GameObject*>* OBComList)
{
	for (unsigned i = 0; i < m_ObList.size(); ++i)
	{
		ObserverBase* ob = m_ObList.at(i);
		if (!ob->m_bActive)
			continue;
		for (unsigned j = 0; j < m_Messages.size(); ++j)
		{
			Message* message = m_Messages.at(j);
			ob->Notify(message->m_Com, message->m_sMessage, OBComList);
		}
	}
	ClearMessages();
}
void GenericSubject::ClearMessages()
{
	for (unsigned j = 0; j < m_Messages.size(); ++j)
	{
		Message* message = m_Messages.at(j);
		delete message;
	}
	m_Messages.clear();
}
void GenericSubject::AddObserver(ObserverBase* in)
{
	// check if exists
	for (unsigned i = 0; i < m_ObList.size(); ++i)
	{
		ObserverBase* ob = m_ObList.at(i);
		if (ob == in)
		{
			DEFAULT_LOG("Observer already added");
			return;
		}
	}
	m_ObList.push_back(in);
}