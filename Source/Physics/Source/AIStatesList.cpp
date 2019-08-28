#include "AIStatesList.h"
#include "DataContainer.h"
#include "Resources.h"

namespace AIStatesList
{
	extern MeleeCombatState Melee = MeleeCombatState();
	extern FleeState Flee = FleeState();
	extern IdleState Idle = IdleState();
	extern IdleState BirdIdle = IdleState(0, 3);
	extern WanderState Wander = WanderState(&Idle);
	extern WanderState BirdWander = WanderState(&BirdIdle, 2, 5);
	extern RangedState Ranged = RangedState();
	extern BossCombat Boss = BossCombat();
	extern BossShockwaveState ShockWave = BossShockwaveState();
}