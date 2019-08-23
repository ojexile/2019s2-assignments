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
	proj->TRANS->SetScale(2.);
	proj->RIGID->SetVel(Vector3(0, 0, 0));
	
	proj->GetComponent<BlackholeScript>()->SetActive(true);

	proj->PROJECTILE->SetLifespan(5.f);
	proj->PROJECTILE->SetDamage(5.f);
}

void BlackHoleAugment::PassiveEffect()
{
	//go->AddComponent(new BlackholeScript(go->RIGID->GetMass(), 5));
	//go->GetComponent<BlackholeScript>()->SetActive(false);
}

void BlackHoleAugment::RemovePassive()
{

}