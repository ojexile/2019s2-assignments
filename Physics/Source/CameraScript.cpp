#include "CameraScript.h"
#include "Utility.h"
#include "CameraComponent.h"

#define LERP_RATE .05f
CameraScript::CameraScript(GameObject* vTarget)
	:m_vTarget(vTarget)
{
}


CameraScript::~CameraScript()
{
}
void CameraScript::Start()
{
	GetComponent<CameraComponent>()->GetCamera()->SetDir({-1, -1, -1});
}
void CameraScript::Update(double d)
{
	Vector3 newPos;
	Vector3 CurrentPos = GetPosition();
	Vector3 TargetPos = m_vTarget->TRANS->GetPosition();
	Vector3 Offset = { 100,100,100 };
	Vector3 OffsetPosition = TargetPos + Offset;
	newPos.x = Lerp(CurrentPos.x, OffsetPosition.x, LERP_RATE);
	newPos.z = Lerp(CurrentPos.z, OffsetPosition.z, LERP_RATE);
	newPos.y = 100;
	GetTransform()->SetPosition(newPos);
}
