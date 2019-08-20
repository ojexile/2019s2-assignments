#include "CameraScript.h"
#include "Utility.h"
#include "CameraComponent.h"
#include "InputManager.h"
#include "Mtx44.h"
#include "Preferences.h"
#include "Resources.h"

#define LERP_RATE .05f
#define LERP_RATE_M .05f

Vector3 CameraScript::m_vFront;
Vector3 CameraScript::m_vRight;
Vector3 CameraScript::m_vOffset;
Vector3 CameraScript::m_vRotateOffset;
bool CameraScript::m_bIsTopDown;
bool CameraScript::m_bRotating;

CameraScript::CameraScript(GameObject* vTarget)
	:m_vTarget(vTarget)
{
	m_bRotating = false;
	m_fCamDist = std::stof(Preferences::GetPref(Resources::PreferencesTerm::CamDist));
	m_bIsTopDown = false;
}

CameraScript::~CameraScript()
{
}
void CameraScript::Start()
{
	GetComponent<CameraComponent>()->GetCamera()->SetDir({ -1, -1, -1 });
	m_vOffset = { m_fCamDist,m_fCamDist,m_fCamDist };
	m_vRotateOffset = { m_fCamDist,m_fCamDist,m_fCamDist };
	m_vFront = { -1,0,-1 };
	m_vFront.Normalize();
	m_vRight = { 1,0,-1 };
	m_vRight.Normalize();
}
void CameraScript::Update(double d)
{
	if (!m_bIsTopDown)
	{
		m_fCamDist = std::stof(Preferences::GetPref(Resources::PreferencesTerm::CamDist));
		m_vOffset = m_vOffset.Normalized() * m_fCamDist;
		m_vRotateOffset = m_vRotateOffset.Normalized() * m_fCamDist;

		m_vOffset = m_vOffset.Normalized() * m_fCamDist;
		m_vRotateOffset = m_vRotateOffset.Normalized() * m_fCamDist;
		// GetCamera()->SetDir(-m_vOffset.Normalized());
		Vector3 newPos;
		Vector3 CurrentPos = GetPosition();
		Vector3 TargetPos = m_vTarget->TRANS->GetPosition();
		Vector3 OffsetPosition = TargetPos + m_vOffset;
		newPos.x = Lerp(CurrentPos.x, OffsetPosition.x, LERP_RATE);
		newPos.y = Lerp(CurrentPos.y, OffsetPosition.y, LERP_RATE);
		newPos.z = Lerp(CurrentPos.z, OffsetPosition.z, LERP_RATE);
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
			//
			m_vFront = rot * m_vFront;
			m_vRight = rot * m_vRight;
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
			//
			m_vFront = rot * m_vFront;
			m_vRight = rot * m_vRight;
			m_bRotating = true;
			bTriggerCW = true;
		}
		if (m_bRotating)
		{
			Rotate();
		}
	}
	else
	{
		Vector3 Pos = m_vTarget->TRANS->GetPosition();
		Pos.x += m_vRotateOffset.x / 100;
		Pos.z += m_vRotateOffset.z / 100;
		Pos.y += 50;
		GetTransform()->SetPosition(Pos);
		GetCamera()->SetDir(m_vTarget->TRANS->GetPosition() - Pos);
	}
}
void CameraScript::Rotate()
{
	// Move Camera
	Vector3 newPos;
	Vector3 CurrentPos = GetPosition();
	Vector3 PlayerPos = m_vTarget->TRANS->GetPosition();
	Vector3 TargetPos = PlayerPos + m_vRotateOffset;
	newPos.x = Lerp(CurrentPos.x, TargetPos.x, LERP_RATE_M);
	newPos.z = Lerp(CurrentPos.z, TargetPos.z, LERP_RATE_M);
	newPos.y = TargetPos.y;
	if (IsClose(newPos, TargetPos, 0.05f))
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
Vector3 CameraScript::GetFront()
{
	return m_vFront;
}
Vector3 CameraScript::GetRight()
{
	return m_vRight;
}
Vector3 CameraScript::GetOffset()
{
	return m_vOffset;
}
Vector3 CameraScript::GetRotateOffset()
{
	return m_vRotateOffset;
}
void CameraScript::SetTopDown(bool b)
{
	if (b)
		m_bRotating = true;
	m_bIsTopDown = b;
}