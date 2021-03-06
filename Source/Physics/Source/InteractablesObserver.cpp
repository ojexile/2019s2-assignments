#include "InteractablesObserver.h"
#include "InteractableObCom.h"

InteractablesObserver::InteractablesObserver()
{
}

InteractablesObserver::~InteractablesObserver()
{
}

void InteractablesObserver::Notify(ComponentBase* com, std::string msg, std::vector<GameObject*>* OBComList)
{
	if (msg != "Interact")
		return;
	for (unsigned i = 0; i < OBComList->size(); i++)
	{
		GameObject* go = OBComList->at(i);
		InteractableObCom* ioc = go->GetComponent<InteractableObCom>(true);
		if (ioc)
		{
			ioc->Notify(com, msg);
		}
	}
}