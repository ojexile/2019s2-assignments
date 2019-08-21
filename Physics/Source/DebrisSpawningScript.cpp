#include "DebrisSpawningScript.h"
#include "DataContainer.h"
#include "Rigidbody.h"
#include "AdvancedParticleSpawnerScript.h"

DebrisSpawningScript::DebrisSpawningScript()
	: m_sDebrisName(""),
	m_iMax(3),
	m_iMin(2)
{
}

DebrisSpawningScript::DebrisSpawningScript(std::string name, int min, int max)
	: m_sDebrisName(name),
	m_iMax(max),
	m_iMin(min)
{
}

DebrisSpawningScript::~DebrisSpawningScript()
{
}

void DebrisSpawningScript::SetDebrisName(std::string name)
{
	this->m_sDebrisName = name;
}

void DebrisSpawningScript::SetMinMax(int min, int max)
{
	m_iMax = max;
	m_iMin = min;
}

void DebrisSpawningScript::Trigger()
{
	int spawncount = Math::RandIntMinMax(m_iMin, m_iMax);
	
	LZ_LOG("rokspawned");
	for (int i = 0; i <	 spawncount; i++)
	{
		auto go = Instantiate(DataContainer::GetInstance()->GetGameObject(m_sDebrisName));
		go->RIGID->AddForce(Vector3(Math::RandFloatMinMax(-1000, 1000), Math::RandFloatMinMax(100, 1000), Math::RandFloatMinMax(-1000, 1000)));
		Vector3 pos = this->TRANS->GetPosition();
		go->TRANS->SetPosition(pos);
	}
	
	auto a_particle = GetComponent<AdvancedParticleSpawnerScript>();
	if (a_particle)
	{
		a_particle->Trigger();
	}

	DestroySelf();
}


