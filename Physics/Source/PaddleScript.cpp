#include "PaddleScript.h"
#include "KeyboardManager.h"
#include "WorldValues.h"

#define maxdeg 70.f
#define defdeg 120.f
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
		float deg = GetComponent<TransformComponent>()->GetDegrees();
		if (KeyboardManager::GetInstance()->GetKeyDown("paddleLeft"))
		{
			if (deg <= -defdeg + maxdeg)
				GetComponent<ChengRigidbody>()->SetTorque({ 0,WorldValues::PaddleForce,0 });
			else
				GetComponent<ChengRigidbody>()->SetAVel({ 0,0,0 });
		}
		else
		{
			if (deg >= -defdeg)
				GetComponent<ChengRigidbody>()->SetTorque({ 0,-WorldValues::PaddleForce,0 });
			else
				GetComponent<ChengRigidbody>()->SetAVel({ 0,0,0 });
		}
		deg = Math::Clamp(deg, -defdeg, -defdeg + maxdeg);
		GetComponent<TransformComponent>()->SetRotation(deg, 0, 1, 0);
	}
	else
	{
		// Constrain
		float deg = GetComponent<TransformComponent>()->GetDegrees();
		if (KeyboardManager::GetInstance()->GetKeyDown("paddleRight"))
		{
			if (deg >= defdeg - maxdeg)
				GetComponent<ChengRigidbody>()->SetTorque({ 0, -WorldValues::PaddleForce,0 });
			else
				GetComponent<ChengRigidbody>()->SetAVel({ 0,0,0 });
		}
		else
		{
			if (deg <= defdeg)
				GetComponent<ChengRigidbody>()->SetTorque({ 0,WorldValues::PaddleForce,0 });
			else
				GetComponent<ChengRigidbody>()->SetAVel({ 0,0,0 });
		}
		deg = Math::Clamp(deg, -defdeg - maxdeg, defdeg);
		GetComponent<TransformComponent>()->SetRotation(deg, 0, 1, 0);
	}
}