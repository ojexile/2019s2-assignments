#include "InteractableObCom.h"
#include "InteractablesObserver.h"
// ---- scripts
#include "FlipEntityScript.h"

InteractableObCom::InteractableObCom()
{
}

InteractableObCom::~InteractableObCom()
{
}
void InteractableObCom::Notify(ComponentBase* com, std::string msg)
{
	CHENG_LOG("Yeet", vtos(GetPosition()));
	FlipEntityScript* flipscript = GetComponent<FlipEntityScript>();
	if (flipscript && !flipscript->IsAlreadyTriggered())
	{
		LZ_LOG("flipentityscript rock yeeted");
		flipscript->Trigger(com);
	}
}