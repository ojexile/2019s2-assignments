#include "CoinPickupScript.h"
#include "PlayerScript.h"


CoinPickupScript::CoinPickupScript()
{
}


CoinPickupScript::~CoinPickupScript()
{
}


void CoinPickupScript::Collide(GameObject* go)
{
	PlayerScript* ps = go->GetComponent<PlayerScript>(true);
	if (ps)
	{
		ps->AddCoin();
		DestroySelf();
	}
}