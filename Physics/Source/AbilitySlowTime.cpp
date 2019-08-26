#include "AbilitySlowTime.h"
#include "Preferences.h"
#include "Resources.h"
#include "PlayerScript.h"
#include "WorldValues.h"

AbilitySlowTime::AbilitySlowTime(const float usetime, const float cooldowntime, const float cost, float maxoffset, const float timescale)
	: AbilityBase(usetime, cooldowntime, cost),
	m_fMaxOffset(maxoffset),
	m_fOverrideTimeScale(timescale)
{
}

AbilitySlowTime::~AbilitySlowTime()
{
}

void AbilitySlowTime::Use(Component* com)
{
	WorldValues::TimeScale = 0.5f;
	float fCamDist = std::stof(Preferences::GetPref(Resources::PreferencesTerm::CamDist));
	Preferences::SetPref(Resources::PreferencesTerm::CamDist, std::to_string(fCamDist - m_fMaxOffset));

	com->GetComponent<PlayerScript>()->GetValues()->OffsetStamina(m_fStaminaCost);
	m_bInUse = true;
	m_bOneTimeTrigger = true;
	m_SW.Start();
}

void AbilitySlowTime::StopUse(Component* com)
{
	if (!m_bOneTimeTrigger)
		return;
	
	WorldValues::TimeScale = WorldValues::DefaultTimeScale;
	float fCamDist = std::stof(Preferences::GetPref(Resources::PreferencesTerm::CamDist));
	Preferences::SetPref(Resources::PreferencesTerm::CamDist, std::to_string(fCamDist + m_fMaxOffset));
	m_bOneTimeTrigger = false;
}
