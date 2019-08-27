#include "InteractableObCom.h"
#include "InteractablesObserver.h"
// ---- scripts
#include "FlipEntityScript.h"
#include "SpawnLootScript.h"
#include "SceneManager.h"
#include "DataContainer.h"
#include "ParticleSpawnerScript.h"
#include "AdvancedParticleSpawnerScript.h"
#include "ScalePatternScript.h"

#define INTERACTDISTSQ 10.f // about 3.f, pretty generous

InteractableObCom::InteractableObCom()
{
}

InteractableObCom::~InteractableObCom()
{
}
void InteractableObCom::Notify(ComponentBase* com, std::string msg)
{
	// reminder to self; this: the GO with the object. com: the player.

	float distanceSq = (this->GetPosition() - com->TRANS->GetPosition()).LengthSquared();

	if (distanceSq > INTERACTDISTSQ) // if you're too far,
		return;						// return.

	CHENG_LOG("Yeet", vtos(GetPosition()));
	FlipEntityScript* flipscript = GetComponent<FlipEntityScript>(true);
	if (flipscript && !flipscript->IsAlreadyTriggered())
	{

		LZ_LOG("flipentityscript rock yeeted");
		flipscript->Trigger(com);
		return;
	}

	SpawnLootScript* lootscript = GetComponent<SpawnLootScript>();
	if (lootscript)
	{
		if (lootscript->m_isActivated)
			return;

		// boolean to flip
		lootscript->m_isActivated = true;
		lootscript->GetGO()->AddComponent(new ScalePatternScript(ScalePatternScript::SHRINK, 1.f, 1.f));

		auto dasd = DataContainer::GetInstance()->GetGameObject("treasureball");
		GameObject* loot = Instantiate(dasd, Vector3(0, 0, 0));
		float yoffset = (TRANS->GetScale() * 1.1f).y;
		loot->TRANS->SetPosition(this->GetPosition() + Vector3(0, yoffset, 0));

		loot->AddComponent(new ParticleSpawnerScript(DataContainer::GetInstance()->GetGameObjectRaw("particlebullettrail"), 30, Vector3(), 0));

		return;
	}
}