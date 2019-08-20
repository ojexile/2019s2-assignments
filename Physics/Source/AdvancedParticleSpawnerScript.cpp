#include "AdvancedParticleSpawnerScript.h"

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
