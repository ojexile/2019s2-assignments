#include "DestructibleEntityScript.h"
#include "RenderComponent.h"

DestructibleEntityScript::DestructibleEntityScript()
	: EntityScript(),
	m_sMessage("")
{
}

DestructibleEntityScript::DestructibleEntityScript(std::string s)
	: EntityScript(),
	m_sMessage(s)
{
}

DestructibleEntityScript::~DestructibleEntityScript()
{
	// delete m_particleSpawnerRef;
}

void DestructibleEntityScript::Update(double dt)
{
	// Check death
	if (GetValues()->GetHealth() <= 0)
	{
		if (m_sMessage == "")
		{
			Notify("DestructibleEntityDied");
		}
		else
			Notify(m_sMessage);

		//destroy self
		return;
	}
	if (m_SW.Stop()->GetTime() >= DAMAGE_TIME)
	{
	}
	if (IsDamageAnim())
	{
	}
}

void DestructibleEntityScript::Collide(GameObject *)
{
}

void DestructibleEntityScript::SetMessage(std::string s)
{
	m_sMessage = s;
}