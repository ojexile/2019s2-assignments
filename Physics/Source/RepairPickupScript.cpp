#include "RepairPickupScript.h"
#include "PlayerScript.h"
#include "GunScript.h"


RepairPickupScript::RepairPickupScript()
{
}


RepairPickupScript::~RepairPickupScript()
{
}

void RepairPickupScript::Collide(GameObject* go)
{
	PlayerScript* ps = go->GetComponent<PlayerScript>();
	if (ps)
	{
		//Gun is always the 1st child of the player
		GunScript* gun = ps->GetChild(1)->GUN;


	}
}