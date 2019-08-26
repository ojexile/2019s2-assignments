#include "BlackHoleAugment.h"
#include "EntityScript.h"
#include "ProjectileScript.h"
#include "TransformComponent.h"
#include "RenderComponent.h"
#include "BlackholeScript.h"


BlackHoleAugment::BlackHoleAugment()
{
	m_AugmentType = BULLET;
}


BlackHoleAugment::~BlackHoleAugment()
{
}

void BlackHoleAugment::ActiveEffect(Component* proj, GameObject* go)
{
	//Bullet expands & becomes a black hole
	proj->GetGO()->AddComponent(new BlackholeScript(go->RIGID->GetMass(), 5));
	
	proj->TRANS->SetScale(1.f);
	proj->RIGID->SetVel(Vector3(0, 0, 0));
	proj->RIGID->SetResponseActive(false);
	proj->PROJECTILE->SetLifespan(1.f);
	proj->PROJECTILE->SetDamage(10.f);
	
	proj->GetComponent<BlackholeScript>()->SetActive(false);
}

void BlackHoleAugment::PassiveEffect()
{
	RYAN_LOG("BLACK_HOLE");
}

void BlackHoleAugment::RemovePassive()
{

}