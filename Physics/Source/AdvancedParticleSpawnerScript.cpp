#include "AdvancedParticleSpawnerScript.h"
#include "ComponentMacros.h"
#include "ParticleScript.h"
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
	particle
	m_fCurrentTime += (float)dt;

	if (m_fCurrentTime <= m_fSpawnRate)
		return;

	do
	{
		GameObject* go = Instantiate(m_ParticleRef, m_sLayer);
		float scalar = go->PARTICLE->GetVel().Length();
		if (scalar < Math::EPSILON)
			scalar = 1.f;
		float q1x, q1z;

		if (m_spawnerType == SPEW)
		{
			for (int i = 0; i <= m_iSpawnCount; i++)
			{
				q1x = Math::RandFloatMinMax(-1.f, 1.f);
				q1z = Math::RandFloatMinMax(-1.f, 1.f);

				go->PARTICLE->SetVel(scalar * Vector3(q1x, 0, q1z));

			}
		}

		else if (m_spawnerType == CIRCULAR)
		{
			float spaceperdegree = 360.f / (float)m_iSpawnCount;

			for (float i = 0.f; i < 360.f; i += spaceperdegree)
			{
				float scalar = go->PARTICLE->GetVel().Length();

				if ((int)i >= 270)
				{
					if ((int)i == 270)
					{
						go->PARTICLE->SetVel(scalar * Vector3(0, 0, -1));
						go->TRANS->SetPosition(TRANS->GetPosition());
					}
					q1z = tan(i);
					q1x = sqrt(1.f - q1z * q1z);
					Vector3 vector = Vector3(q1x, 0, -q1z);
					go->PARTICLE->SetVel(scalar * vector);
					go->TRANS->SetPosition(TRANS->GetPosition());
				}
				else if ((int)i >= 180)
				{
					if ((int)i == 180)
					{
						go->PARTICLE->SetVel(scalar * Vector3(-1, 0, 0));
						go->TRANS->SetPosition(TRANS->GetPosition());
					}
					q1z = tan(i);
					q1x = sqrt(1.f - q1z * q1z);
					Vector3 vector = Vector3(-q1x, 0, -q1z);
					go->PARTICLE->SetVel(scalar * vector);
					go->TRANS->SetPosition(TRANS->GetPosition());
				}
				else if ((int)i >= 90)
				{
					if ((int)i == 90)
					{
						go->PARTICLE->SetVel(scalar * Vector3(0, 0, 1));
						go->TRANS->SetPosition(TRANS->GetPosition());
					}
					q1z = sin(i);
					q1x = sqrt(1.f - q1z * q1z);
					Vector3 vector = Vector3(-q1x, 0, q1z);
					go->PARTICLE->SetVel(scalar * vector);
					go->TRANS->SetPosition(TRANS->GetPosition());
				}
				else if ((int)i >= 0)
				{
					if ((int)i == 0)
					{
						go->PARTICLE->SetVel(scalar * Vector3(1, 0, 0));
						go->TRANS->SetPosition(TRANS->GetPosition());
					}
					q1z = sin(i);
					q1x = sqrt(1.f - q1z * q1z);
					Vector3 vector = Vector3(q1x, 0, q1z);
					go->PARTICLE->SetVel(scalar * vector);
					go->TRANS->SetPosition(TRANS->GetPosition());
				}
			}


		}

		m_fCurrentTime -= m_fSpawnRate;
	} while (m_fCurrentTime >= m_fSpawnRate);
}

void AdvancedParticleSpawnerScript::Trigger()
{
	if (!m_bOneTimeTrigger)
		return;
	if (m_Triggered)
		return;

	if (m_spawnerType == SPEW)
		for (int i = 0; i <= m_iSpawnCount; i++)
		{
			GameObject* go = Instantiate(m_ParticleRef, m_sLayer);
			float scalar = go->PARTICLE->GetVel().Length();
			if (scalar < Math::EPSILON)
				scalar = 1.f;
			float q1x, q1z;


			{
				q1x = Math::RandFloatMinMax(-1.f, 1.f);
				q1z = Math::RandFloatMinMax(-1.f, 1.f);

				go->PARTICLE->SetVel(scalar * Vector3(q1x, 0, q1z));
				go->TRANS->SetPosition(TRANS->GetPosition());
			}

		}


	else if (m_spawnerType == CIRCULAR)
	{


		float spaceperdegree = 360.f / (float)m_iSpawnCount;

		for (float i = 0.f; i < 360.f; i += spaceperdegree)
		{
			GameObject* go = Instantiate(m_ParticleRef, m_sLayer);
			float scalar = go->PARTICLE->GetVel().Length();
			if (scalar < Math::EPSILON)
				scalar = 1.f;
			float q1x, q1z;

			go->PARTICLE->SetVel(scalar * Vector3(cos(i), 0, sin(i)));
			go->TRANS->SetPosition(TRANS->GetPosition());
			//float scalar = go->PARTICLE->GetVel().Length();

		//	if ((int)i >= 270)
		//	{
		//		if ((int)i == 270)
		//		{
		//			go->PARTICLE->SetVel(scalar * Vector3(0, 0, -1));
		//			go->TRANS->SetPosition(TRANS->GetPosition());
		//		}
		//		q1z = tan(i);
		//		q1x = sqrt(1.f - q1z * q1z);
		//		Vector3 vector = Vector3(q1x, 0, -q1z);
		//		go->PARTICLE->SetVel(scalar * vector);
		//		go->TRANS->SetPosition(TRANS->GetPosition());
		//	}
		//	else if ((int)i >= 180)
		//	{
		//		if ((int)i == 180)
		//		{
		//			go->PARTICLE->SetVel(scalar * Vector3(-1, 0, 0));
		//			go->TRANS->SetPosition(TRANS->GetPosition());
		//		}
		//		q1z = tan(i);
		//		q1x = sqrt(1.f - q1z * q1z);
		//		Vector3 vector = Vector3(-q1x, 0, -q1z);
		//		go->PARTICLE->SetVel(scalar * vector);
		//		go->TRANS->SetPosition(TRANS->GetPosition());
		//	}
		//	else if ((int)i >= 90)
		//	{
		//		if ((int)i == 90)
		//		{
		//			go->PARTICLE->SetVel(scalar * Vector3(0, 0, 1));
		//			go->TRANS->SetPosition(TRANS->GetPosition());
		//		}
		//		q1z = sin(i);
		//		q1x = sqrt(1.f - q1z * q1z);
		//		Vector3 vector = Vector3(-q1x, 0, q1z);
		//		go->PARTICLE->SetVel(scalar * vector);
		//		go->TRANS->SetPosition(TRANS->GetPosition());
		//	}
		//	else if ((int)i >= 0)
		//	{
		//		if ((int)i == 0)
		//		{
		//			go->PARTICLE->SetVel(scalar * Vector3(1, 0, 0));
		//			go->TRANS->SetPosition(TRANS->GetPosition());
		//		}
		//		else
		//		{
		//			q1z = cos(i);
		//			q1x = sin(i);
		//			//q1x = sin(1.f - q1z * q1z);
		//			Vector3 vector = Vector3(q1x, 0, q1z);
		//			go->PARTICLE->SetVel(scalar * vector);
		//			go->TRANS->SetPosition(TRANS->GetPosition());
		//		}
		//	}
		//}
		}
	}
	m_Triggered = true;

}



void AdvancedParticleSpawnerScript::ResetTrigger()
{
	m_Triggered = false;
}
