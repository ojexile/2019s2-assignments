#include "ChargeBarScript.h"

ChargeBarScript::ChargeBarScript(GauntletScript* GS, GameObject* Part)
	: m_GS(GS)
	, m_Part(Part)
{
}

ChargeBarScript::~ChargeBarScript()
{
}

void ChargeBarScript::Update(double dt)
{
	const float MAX_SIZE = 400;
	float percentage = max(m_GS->m_fCharge / 100.f * MAX_SIZE, 0.01f);
	GetTransform()->SetScale(percentage, 25, 1);
	GetComponent<RenderComponent>()->SetColor({ percentage,0 ,percentage });

	if (m_GS->m_fCharge == 100.f)
		m_Part->SetActive(true);
	else
		m_Part->SetActive(false);
}