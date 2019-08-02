#include "AmmoDumpScript.h"

AmmoDumpScript::AmmoDumpScript()
{
}

AmmoDumpScript::~AmmoDumpScript()
{
}

void AmmoDumpScript::Collide(GameObject* go)
{
	ChengPlayerScript* s = go->GetComponent<ChengPlayerScript>();
	if (s)
	{
		s->RefillAmmo();
		DestroySelf();
	}
}