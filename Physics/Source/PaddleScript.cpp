#include "PaddleScript.h"
#include "KeyboardManager.h"
#define SPEED 1500.f
PaddleScript::PaddleScript(bool b)
{
	m_bIsLeft = b;
}

PaddleScript::~PaddleScript()
{
}
void PaddleScript::Update(double dt)
{
	if (m_bIsLeft)
	{
		if (KeyboardManager::GetInstance()->GetKeyDown("paddleLeft"))
		{
			GetComponent<ChengRigidbody>()->SetAVel({ 0,SPEED,0 });
		}
		else
		{
			GetComponent<ChengRigidbody>()->SetAVel({ 0,-SPEED,0 });
		}
		// Constrain
		const float maxdeg = 70;
		float deg = GetComponent<TransformComponent>()->GetDegrees();
		deg = Math::Clamp(deg, -90.f, -90 + maxdeg);
		GetComponent<TransformComponent>()->SetRotation(deg, 0, 1, 0);
	}
	else
	{
		if (KeyboardManager::GetInstance()->GetKeyDown("paddleRight"))
		{
			GetComponent<ChengRigidbody>()->SetAVel({ 0, -SPEED,0 });
		}
		else
		{
			GetComponent<ChengRigidbody>()->SetAVel({ 0,SPEED,0 });
		}
		// Constrain
		const float maxdeg = 70;
		float deg = GetComponent<TransformComponent>()->GetDegrees();
		deg = Math::Clamp(deg, 90.f - maxdeg, 90.f);
		GetComponent<TransformComponent>()->SetRotation(deg, 0, 1, 0);
	}
}