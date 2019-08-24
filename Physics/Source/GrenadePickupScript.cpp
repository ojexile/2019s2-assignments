#include "GrenadePickupScript.h"
#include "PlayerScript.h"


GrenadePickupScript::GrenadePickupScript()
{
}


GrenadePickupScript::~GrenadePickupScript()
{
}


void GrenadePickupScript::Collide(GameObject* go)
{
	PlayerScript* ps = go->GetComponent<PlayerScript>();
	if (ps)
	{
		ps->AddGrenade();
		DestroySelf();
	}
}