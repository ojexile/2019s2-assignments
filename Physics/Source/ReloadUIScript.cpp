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
	TRANS->SetRelativeScale({ MAX_SCALE, 1,1 });
	// TRANS->SetRelativeRotation(-GetTransform()->GetRelativeDegrees(), TRANS->GetRelativeRotation());
}

void ReloadUIScript::Start()
{
	Vector3 Pos = m_ParentGO->TRANS->GetRelativePosition();
	TRANS->SetRelativePosition(-MAX_SCALE / 2, 1, 0);
}