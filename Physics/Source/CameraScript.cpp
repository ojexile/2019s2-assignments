#include "CameraScript.h"
#include "Utility.h"
#include "CameraComponent.h"
#include "InputManager.h"
#include "Mtx44.h"

#define LERP_RATE .05f
#define LERP_RATE_M .05f
#define DISTANCE 50
CameraScript::CameraScript(GameObject* vTarget)
	:m_vTarget(vTarget)
{
	m_bRotating = false;
}


CameraScript::~CameraScript()
{
}
void CameraScript::Start()
{
	GetComponent<CameraComponent>()->GetCamera()->SetDir({-1, -1, -1});
	m_vOffset = { DISTANCE,DISTANCE,DISTANCE };
	m_vRotateOffset = { DISTANCE,DISTANCE,DISTANCE };
}
void CameraScript::Update(double d)
{
	Vector3 newPos;
	Vector3 CurrentPos = GetPosition();
	Vector3 TargetPos = m_vTarget->TRANS->GetPosition();
	Vector3 OffsetPosition = TargetPos + m_vOffset;
	newPos.x = Lerp(CurrentPos.x, OffsetPosition.x, LERP_RATE);
	newPos.z = Lerp(CurrentPos.z, OffsetPosition.z, LERP_RATE);
	newPos.y = DISTANCE;
	GetTransform()->SetPosition(newPos);

	static bool bTriggerCCW = false;
	if (!InputManager::GetInstance()->GetInputStrength("CameraRotateCCW"))
	{
		bTriggerCCW = false;
	}
	if (InputManager::GetInstance()->GetInputStrength("CameraRotateCCW") && !bTriggerCCW)
	{
		Mtx44 rot;
		rot.SetToRotation(90, 0, 1, 0);
		m_vRotateOffset = rot * m_vRotateOffset;
		m_vRotateOffset.x = round(m_vRotateOffset.x);
		m_vRotateOffset.z = round(m_vRotateOffset.z);
		m_bRotating = true;
		bTriggerCCW = true;
	}
	static bool bTriggerCW = false;
	if (!InputManager::GetInstance()->GetInputStrength("CameraRotateCW"))
	{
		bTriggerCW = false;
	}
	if (InputManager::GetInstance()->GetInputStrength("CameraRotateCW") && !bTriggerCW)
	{
		Mtx44 rot;
		rot.SetToRotation(-90, 0, 1, 0);
		m_vRotateOffset = rot * m_vRotateOffset;
		m_vRotateOffset.x = round(m_vRotateOffset.x);
		m_vRotateOffset.z = round(m_vRotateOffset.z);
		m_bRotating = true;
		bTriggerCW = true;
	}
	if (m_bRotating)
	{
		Rotate();
	}
}
void CameraScript::Rotate()
{
	// Move Camera
	Vector3 newPos;
	Vector3 CurrentPos = GetPosition();
	Vector3 PlayerPos = m_vTarget->TRANS->GetPosition();
	Vector3 TargetPos = PlayerPos + m_vRotateOffset;
	TargetPos.y = m_vRotateOffset.y;
	newPos.x = Lerp(CurrentPos.x, TargetPos.x, LERP_RATE_M);
	newPos.z = Lerp(CurrentPos.z, TargetPos.z, LERP_RATE_M);
	newPos.y = DISTANCE;
	if (IsClose(newPos, TargetPos, 1.f))
	{
		m_bRotating = false;
		newPos = TargetPos;
	}
	GetTransform()->SetPosition(newPos);
	// Cam Dir
	Vector3 CamToPlayer = PlayerPos - GetPosition();
	GetCamera()->SetDir(CamToPlayer);
	// Update Offset
	m_vOffset = -CamToPlayer;
}