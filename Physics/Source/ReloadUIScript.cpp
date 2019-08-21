#include "ReloadUIScript.h"
#include "WeaponScript.h"
#define MAX_SCALE 3.f
ReloadUIScript::ReloadUIScript()
{
}

ReloadUIScript::~ReloadUIScript()
{
}

void ReloadUIScript::Update(double dt)
{
	//if (!m_ParentGO->GUN->IsReloading())
	//	SetActive(false);
	float fYScale = 0.5f;
	float fXScale = m_ParentGO->GUN->GetReloadElapsedTime() / m_ParentGO->GUN->GetReloadTime() * MAX_SCALE;
	if (fXScale > 0.1f)
		TRANS->SetRelativeScale({ fXScale, fYScale,1 });
	else
		TRANS->SetRelativeScale({ 0.1f, fYScale,1 });
}

void ReloadUIScript::Start()
{
	Vector3 Pos = m_ParentGO->TRANS->GetRelativePosition();
	TRANS->SetRelativePosition(0, 1, -Pos.z);
}