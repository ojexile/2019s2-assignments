#include "BlackHoleAugment.h"
#include "EntityScript.h"
#include "ProjectileScript.h"
#include "TransformComponent.h"
#include "RenderComponent.h"
#include "BlackholeScript.h"


BlackHoleAugment::BlackHoleAugment()
{
}


BlackHoleAugment::~BlackHoleAugment()
{
}

void BlackHoleAugment::ActiveEffect(Component* proj, GameObject* go)
{
	//Bullet expands & becomes a black hole
	proj->TRANS->SetScale(1.5);
	proj->PROJECTILE->SetLifespan(1.5f);
	proj->PROJECTILE->SetDamage(5.f);
}

void BlackHoleAugment::PassiveEffect(GameObject* go)
{
	go->AddComponent(new Blackhole(go->RIGID->GetMass(), 5));
}