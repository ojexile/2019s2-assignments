#include "InteractableObCom.h"
#include "InteractablesObserver.h"
// ---- scripts
#include "FlipEntityScript.h"
#include "SpawnLootScript.h"
#include "SceneManager.h"
#include "DataContainer.h"

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
		return;
	}
	SpawnLootScript* lootscript = GetComponent<SpawnLootScript>();
	if (lootscript)
	{
		auto dasd = DataContainer::GetInstance()->GetGameObject("treasureball");
		GameObject* loot = Instantiate(dasd, Vector3( 0,0,0 ));
		float yoffset = (TRANS->GetScale() * 1.1).y;
		loot->TRANS->SetPosition(this->GetPosition() + Vector3(0, yoffset, 0));
		loot->RIGID->AddForce({ 100,100,100 });

		return;
	}
}