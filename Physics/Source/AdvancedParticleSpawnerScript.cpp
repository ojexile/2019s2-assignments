#include "AdvancedParticleSpawnerScript.h"
#include "ComponentMacros.h"
#include "Rigidbody.h"

AdvancedParticleSpawnerScript::AdvancedParticleSpawnerScript(eSpawnerType type, int spawncount, bool isonetimetrigger, GameObject * refobj, float spawnrate, Vector3 spawnradius, const float sizeoffset, std::string layer, float lifeftime)
	: ParticleSpawnerScript(refobj, spawnrate, spawnradius, sizeoffset, layer, lifeftime),
	m_spawnerType(type),
	m_bOneTimeTrigger(isonetimetrigger),
	m_iSpawnCount(spawncount),
	m_Triggered(false)
{
}

AdvancedParticleSpawnerScript::~AdvancedParticleSpawnerScript()
{

}

void AdvancedParticleSpawnerScript::Update(double dt)
{
	if (m_bOneTimeTrigger)
		return;

	if (m_fCurrentTime <= m_fSpawnRate)
		return;

	GameObject* go = Instantiate(m_ParticleRef, m_sLayer);
	float scalar = go->RIGID->GetVel().Length();
	if (scalar < Math::EPSILON)
		scalar = 1.f;
	float q1x, q1z;

	if (m_spawnerType == SPEW)
	{
		q1x = Math::RandFloatMinMax(-1.f, 1.f);
		q1z = Math::RandFloatMinMax(-1.f, 1.f);

		go->RIGID->AddForce(scalar * Vector3(q1x, 0, q1z));
	}

	else if (m_spawnerType == CIRCULAR)
	{
		float spaceperdegree = 360.f / (float)m_iSpawnCount;

		for (float i = 0.f; i < 360.f; i += spaceperdegree)
		{
			float scalar = go->RIGID->GetVel().Length();
			
			if ((int)i >= 270)
			{
				if ((int)i == 270)
				{
					go->RIGID->SetVel(scalar * Vector3(0, 0, -1));
					go->TRANS->SetPosition(TRANS->GetPosition());
				}
				q1z = tan(i);
				q1x = sqrt(1.f - q1z * q1z);
				Vector3 vector = Vector3(q1x, 0, -q1z);
				go->RIGID->AddForce(scalar * vector);
				go->TRANS->SetPosition(TRANS->GetPosition());
			}
			else if ((int)i >= 180)
			{
				if ((int)i == 180)
				{
					go->RIGID->SetVel(scalar * Vector3(-1, 0, 0));
					go->TRANS->SetPosition(TRANS->GetPosition());
				}
				q1z = tan(i);
				q1x = sqrt(1.f - q1z * q1z);
				Vector3 vector = Vector3(-q1x, 0, -q1z);
				go->RIGID->AddForce(scalar * vector);
				go->TRANS->SetPosition(TRANS->GetPosition());
			}
			else if ((int)i >= 90)
			{
				if ((int)i == 90)
				{
					go->RIGID->SetVel(scalar * Vector3(0, 0, 1));
					go->TRANS->SetPosition(TRANS->GetPosition());
				}
				q1z = sin(i);
				q1x = sqrt(1.f - q1z * q1z);
				Vector3 vector = Vector3(-q1x, 0, q1z);
				go->RIGID->AddForce(scalar * vector);
				go->TRANS->SetPosition(TRANS->GetPosition());
			}
			else if ((int)i >= 0)
			{
				if ((int)i == 0)
				{
					go->RIGID->SetVel(scalar * Vector3(1, 0, 0));
					go->TRANS->SetPosition(TRANS->GetPosition());
				}
				q1z = sin(i);
				q1x = sqrt(1.f - q1z * q1z);
				Vector3 vector = Vector3(q1x, 0, q1z);
				go->RIGID->AddForce(scalar * vector);
				go->TRANS->SetPosition(TRANS->GetPosition());
			}
		}
	
	
	}
}

void AdvancedParticleSpawnerScript::Trigger()
{
	if (!m_bOneTimeTrigger)
		return;
	if (m_Triggered)
		return;


	switch (m_spawnerType)
	{
	case SPEW:
		break;
	case CIRCULAR:
		break;
	default:
		break;
	}

	m_Triggered = true;
}
