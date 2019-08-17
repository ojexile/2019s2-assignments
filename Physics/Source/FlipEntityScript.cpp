#include "FlipEntityScript.h"

FlipEntityScript::FlipEntityScript()
	: InteractionBaseScript(),
	m_flipDirection(FLIP_NONE),
	m_fRotationAmount(0.f)
{
	
}

FlipEntityScript::~FlipEntityScript()
{
}

void FlipEntityScript::Update(double dt)
{
}

void FlipEntityScript::Trigger(GameObject * go, GameObject * go2)
{
}
