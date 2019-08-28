#pragma once
#include "AIState.h"
#include "WanderState.h"
#include "MeleeCombatState.h"
#include "FleeState.h"
#include "IdleState.h"
#include "RangedState.h"
#include "BossCombat.h"
#include "BossShockwaveState.h"

namespace AIStatesList
{
	extern MeleeCombatState Melee;
	extern FleeState Flee;
	extern IdleState Idle;
	extern IdleState BirdIdle;
	extern WanderState Wander;
	extern WanderState BirdWander;
	extern RangedState Ranged;
	extern BossCombat Boss;
	extern BossShockwaveState ShockWave;
}