#include "ExplodeAugment.h"
#include "GunScript.h"
#include "EntityScript.h"
#include "ProjectileScript.h"
#include "TransformComponent.h"
#include "RenderComponent.h"

ExplodeAugment::ExplodeAugment()
{
	m_AugmentType = BULLET;
}

ExplodeAugment::~ExplodeAugment()
{
}

void ExplodeAugment::ActiveEffect(Component* proj, GameObject* go)
{
	if (proj->TRANS->GetScale() == 1.5)
		return;

	Vector3 relDir = go->TRANS->GetPosition() - proj->TRANS->GetPosition();
	EntityScript* es = go->GetComponent<EntityScript>();

	//Entity gets damaged and pushed back
	es->Damage((int)(proj->GetComponent<ProjectileScript>()->GetDamage() * 1.5f));
	go->RIGID->AddForce(relDir.Normalize() * 1000);

	//Bullet expands
	proj->TRANS->SetScale(1.5);
}

void ExplodeAugment::PassiveEffect()
{
	RYAN_LOG("EXPLODE");
}

void ExplodeAugment::RemovePassive()
{
}