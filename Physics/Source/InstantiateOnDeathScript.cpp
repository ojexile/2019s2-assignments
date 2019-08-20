#include "InstantiateOnDeathScript.h"
#include "DataContainer.h"
#include "Rigidbody.h"
InstantiateOnDeathScript::InstantiateOnDeathScript()
	: m_bHasTriggered(false)
{
}

InstantiateOnDeathScript::~InstantiateOnDeathScript()
{
}

GameObject * InstantiateOnDeathScript::AddGOToList(GameObject * go)
{
	return nullptr;
}

void InstantiateOnDeathScript::Update(double dt)
{
	if (!m_bHasTriggered)
		return;

	for (int i; i < 2; i++)
	{
		auto go = Instantiate(DataContainer::GetInstance()->GetGameObject("boulder2"));
		go->RIGID->AddForce(Vector3( Math::RandFloatMinMax(-10000, 10000), Math::RandFloatMinMax(100, 1000), Math::RandFloatMinMax(-1000, 1000) ));
		go->TRANS->SetPosition(TRANS->GetPosition());
	}

}

void InstantiateOnDeathScript::Collide(GameObject * go)
{
	
}

void InstantiateOnDeathScript::Trigger()
{
	for (int i = 0; i != 2; i++)
	{
		auto go = Instantiate(DataContainer::GetInstance()->GetGameObject("boulder2"));
		go->RIGID->AddForce(Vector3(Math::RandFloatMinMax(-1000, 1000), Math::RandFloatMinMax(100, 1000), Math::RandFloatMinMax(-1000, 1000)));
		go->TRANS->SetPosition(TRANS->GetPosition());
	}
}
