#include "PlayerDeathScript.h"
#include "WorldValues.h"

PlayerDeathScript::PlayerDeathScript()
{
	SetActive(false);
}

PlayerDeathScript::~PlayerDeathScript()
{
}

void PlayerDeathScript::Start()
{
	//WorldValues::TimeScale = 0.1f;
}

void PlayerDeathScript::Update(double dt)
{
}