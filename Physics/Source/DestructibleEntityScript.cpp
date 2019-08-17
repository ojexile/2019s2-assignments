#include "DestructibleEntityScript.h"
#include "RenderComponent.h"

DestructibleEntityScript::DestructibleEntityScript()
	: EntityScript()
{
	m_particleSpawnerRef = nullptr;
}

DestructibleEntityScript::DestructibleEntityScript(GameObject * m_particleSpawnerRef)
	: EntityScript()
{
	this->m_particleSpawnerRef = m_particleSpawnerRef;
}

DestructibleEntityScript::~DestructibleEntityScript()
{
	// delete m_particleSpawnerRef;
}

void DestructibleEntityScript::Update(double dt)
{
	// Check death
	if (GetHealth() <= 0)
	{
		if (m_particleSpawnerRef != nullptr)
		{
			TransformComponent* Trans = GetComponent<TransformComponent>();
			Vector3 trans = Trans->GetPosition();
			Instantiate(m_particleSpawnerRef, trans, "Default");
		}
		DestroySelf(); // should switch to play death anim
		return;
	}
	if (GetSW().Stop()->GetTime() >= DAMAGE_TIME)
	{
		SetDamageAnim(false);
		RENDER->ResetColor();
	}
	if (IsDamageAnim())
	{
	}
}

DestructibleEntityScript * DestructibleEntityScript::AttachGameObject(GameObject * go)
{
	m_particleSpawnerRef = go;
	return this;
}