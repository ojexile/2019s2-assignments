#pragma once
#include "AIState.h"
#include "WanderState.h"
#include "MeleeCombatState.h"
#include "FleeState.h"
#include "IdleState.h"
namespace AIStatesList
{
	extern MeleeCombatState Melee;
	extern FleeState Flee;
	extern WanderState Wander;
	extern IdleState Idle;
}