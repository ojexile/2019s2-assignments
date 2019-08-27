#include "DebrisSpawningScript.h"
#include "DataContainer.h"
#include "Rigidbody.h"
#include "AdvancedParticleSpawnerScript.h"

DebrisSpawningScript::DebrisSpawningScript()
	: m_sDebrisName(""),
	m_iMax(3),
	m_iMin(2),
	m_bTriggered(false)
{
}

DebrisSpawningScript::DebrisSpawningScript(std::string name, int min, int max)
	: m_sDebrisName(name),
	m_iMax(max),
	m_iMin(min),
	m_bTriggered(false)
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
	if (m_bTriggered)
		return;

	m_bTriggered = true;

	int spawncount = Math::RandIntMinMax(m_iMin, m_iMax);

	LZ_LOG("rokspawned");
	for (int i = 0; i < spawncount; i++)
	{
		auto go = Instantiate(DataContainer::GetInstance()->GetGameObject(m_sDebrisName));

		float randomAngle = Math::RandFloatMinMax(0.f, Math::TWO_PI);

		go->RIGID->SetVel({ cos(randomAngle) * 4.f , 1.f, sin(randomAngle) * 4.f });
		go->RIGID->AddForce(go->RIGID->GetVel() * Math::RandFloatMinMax(750.f, 1000.f) );

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


