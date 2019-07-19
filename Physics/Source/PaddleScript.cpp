#include "PaddleScript.h"
#include "KeyboardManager.h"
#define SPEED 30000.f
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
		// Constrain
		const float maxdeg = 70;
		float deg = GetComponent<TransformComponent>()->GetDegrees();
		if (KeyboardManager::GetInstance()->GetKeyDown("paddleLeft"))
		{
			if (deg <= -90 + maxdeg)
				GetComponent<ChengRigidbody>()->SetTorque({ 0,SPEED,0 });
			else
				GetComponent<ChengRigidbody>()->SetAVel({ 0,0,0 });
		}
		else
		{
			if (deg >= -90)
				GetComponent<ChengRigidbody>()->SetTorque({ 0,-SPEED,0 });
			else
				GetComponent<ChengRigidbody>()->SetAVel({ 0,0,0 });
		}
		deg = Math::Clamp(deg, -90.f, -90 + maxdeg);
		GetComponent<TransformComponent>()->SetRotation(deg, 0, 1, 0);
	}
	else
	{
		// Constrain
		const float maxdeg = 70;
		float deg = GetComponent<TransformComponent>()->GetDegrees();
		if (KeyboardManager::GetInstance()->GetKeyDown("paddleRight"))
		{
			if (deg >= 90 - maxdeg)
				GetComponent<ChengRigidbody>()->SetTorque({ 0, -SPEED,0 });
			else
				GetComponent<ChengRigidbody>()->SetAVel({ 0,0,0 });
		}
		else
		{
			if (deg <= 90)
				GetComponent<ChengRigidbody>()->SetTorque({ 0,SPEED,0 });
			else
				GetComponent<ChengRigidbody>()->SetAVel({ 0,0,0 });
		}
		deg = Math::Clamp(deg, -90.f - maxdeg, 90.f);
		GetComponent<TransformComponent>()->SetRotation(deg, 0, 1, 0);
	}
}