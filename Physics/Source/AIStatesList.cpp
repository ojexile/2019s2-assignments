#include "AIStatesList.h"
#include "DataContainer.h"
#include "Resources.h"

namespace AIStatesList
{
	extern MeleeCombatState Melee = MeleeCombatState();
	extern FleeState Flee = FleeState();
	extern IdleState Idle = IdleState();
	extern IdleState BirdIdle = IdleState(0, 0);
	extern WanderState Wander = WanderState(&Idle);
	extern WanderState BirdWander = WanderState(&BirdIdle);
	extern RangedState Ranged = RangedState();
	extern BossCombat Boss = BossCombat();
}