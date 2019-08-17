#include "InteractableObCom.h"

InteractableObCom::InteractableObCom()
{
}

InteractableObCom::~InteractableObCom()
{
}
void InteractableObCom::Notify(ComponentBase* com, std::string msg)
{
	CHENG_LOG("Yeet", vtos(GetPosition()));
}