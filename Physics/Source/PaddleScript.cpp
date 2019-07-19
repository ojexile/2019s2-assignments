#include "PaddleScript.h"
#include "KeyboardManager.h"
#define SPEED 5.f
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
			if (deg != -90 + maxdeg)
			{
				GetComponent<ChengRigidbody>()->SetAVel({ 0,SPEED,0 });
			}
		}
		else
		{
			if (deg != -90)
			{
				GetComponent<ChengRigidbody>()->SetAVel({ 0,-SPEED,0 });
			}
		}
	}
	else
	{
		// Constrain
		const float maxdeg = 70;
		float deg = GetComponent<TransformComponent>()->GetDegrees();
		if (KeyboardManager::GetInstance()->GetKeyDown("paddleRight"))
		{
			if (deg != 90 - maxdeg)
				GetComponent<ChengRigidbody>()->SetAVel({ 0, -SPEED,0 });
		}
		else
		{
			if (deg != 90)
				GetComponent<ChengRigidbody>()->SetAVel({ 0,SPEED,0 });
		}
	}
}