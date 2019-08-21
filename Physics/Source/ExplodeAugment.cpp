#include "ExplodeAugment.h"
#include "GunScript.h"
#include "TransformComponent.h"
#include "EntityScript.h"

ExplodeAugment::ExplodeAugment()
{
}


ExplodeAugment::~ExplodeAugment()
{
}

void ExplodeAugment::ActiveEffect(Component* proj, GameObject* go)
{
	Vector3 relDir = go->TRANS->GetPosition() - TRANS->GetPosition();
	EntityScript* es = go->GetComponent<EntityScript>();
	
	es->Damage(20);
	go->RIGID->AddForce(relDir.Normalize() * 1000);
}

void ExplodeAugment::PassiveEffect(GameObject* go)
{

}