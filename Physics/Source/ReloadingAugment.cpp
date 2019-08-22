#include "ReloadingAugment.h"



ReloadingAugment::ReloadingAugment()
{
	m_AugmentType = WEAPON;
}


ReloadingAugment::~ReloadingAugment()
{
}

void ReloadingAugment::ActiveEffect(Component* proj, GameObject* go)
{
	//Bullet expands
	proj->TRANS->SetScale(1.5);
}

void ReloadingAugment::PassiveEffect(GameObject* go)
{

}