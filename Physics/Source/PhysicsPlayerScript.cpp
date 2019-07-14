#include "PhysicsPlayerScript.h"
#include "KeyboardManager.h"
#include "SceneManager.h"
#include "AudioManager.h"
#include "ChengRigidbody.h"
PhysicsPlayerScript::PhysicsPlayerScript(GameObject* goRef, GameObject* goRef2, GameObject* goRef3)
	:m_RefBall(goRef)
	, m_RefBall2(goRef2)
	, m_RefBall3(goRef3)
{
}

PhysicsPlayerScript::~PhysicsPlayerScript()
{
}
void PhysicsPlayerScript::Start()
{
	m_vCameraFront = SceneManager::GetInstance()->GetScene()->GetCamera()->GetTarget();
	m_vCameraUp = SceneManager::GetInstance()->GetScene()->GetCamera()->GetUp();
}
void PhysicsPlayerScript::Update(double dt)
{
	m_vCameraFront = SceneManager::GetInstance()->GetScene()->GetCamera()->GetDir();
	m_vCameraUp = SceneManager::GetInstance()->GetScene()->GetCamera()->GetUp();
	TransformComponent* trans = GetComponent<TransformComponent>();

	float fMoveSpeed = 50 * (float)dt;
	Vector3 vRight = m_vCameraFront.Cross(m_vCameraUp);
	if (KeyboardManager::GetInstance()->GetKeyDown("PlayerMoveForward"))
	{
		trans->Translate(fMoveSpeed * m_vCameraFront);
	}
	if (KeyboardManager::GetInstance()->GetKeyDown("PlayerMoveBackward"))
	{
		trans->Translate(-fMoveSpeed * m_vCameraFront);
	}
	if (KeyboardManager::GetInstance()->GetKeyDown("PlayerMoveLeft"))
	{
		trans->Translate(-fMoveSpeed * vRight);
	}
	if (KeyboardManager::GetInstance()->GetKeyDown("PlayerMoveRight"))
	{
		trans->Translate(fMoveSpeed * vRight);
	}
	if (KeyboardManager::GetInstance()->GetKeyDown("PlayerMoveUp"))
	{
		trans->Translate(fMoveSpeed * m_vCameraUp);
	}
	if (KeyboardManager::GetInstance()->GetKeyDown("PlayerMoveDown"))
	{
		trans->Translate(-fMoveSpeed * m_vCameraUp);
	}
	trans->SetPosition(trans->GetPosition().x, 5, trans->GetPosition().z);
	float fBallSpeed = 130.f;
	Vector3 ballDir = m_vCameraFront;
	Vector3 ballSpawn = SceneManager::GetInstance()->GetScene()->GetCameraGameObject()->GetComponent<TransformComponent>()->GetPosition();
	//ballDir.y = 0;

	if (KeyboardManager::GetInstance()->GetKeyTriggered("spawnBall"))
	{
		GameObject* ball = Instantiate(m_RefBall, ballSpawn);
		ball->GetComponent<ChengRigidbody>()->SetVel(fBallSpeed * ballDir);
	}
	if (KeyboardManager::GetInstance()->GetKeyTriggered("spawnBall2"))
	{
		GameObject* ball = Instantiate(m_RefBall2, ballSpawn);
		ball->GetComponent<ChengRigidbody>()->SetVel(fBallSpeed * ballDir);
	}
	if (KeyboardManager::GetInstance()->GetKeyTriggered("spawnBall3"))
	{
		GameObject* ball = Instantiate(m_RefBall3, ballSpawn);
		ball->GetComponent<ChengRigidbody>()->SetVel(fBallSpeed * ballDir);
	}
	if (KeyboardManager::GetInstance()->GetKeyTriggered("switchCam"))
	{
		SceneManager::GetInstance()->GetScene()->GetCameraGameObject()->GetComponent<CameraComponent>()->SetCameraType(CameraComponent::CAM_ORTHO);
		GameObject* cam = SceneManager::GetInstance()->GetScene()->GetCameraGameObject();
		trans->SetPosition(0, 0, 0);
		cam->GetComponent<TransformComponent>()->SetRelativePosition(0, 200, 0);
		cam->GetComponent<CameraComponent>()->GetCamera()->SetDir({ 0, -1, 0 });
	}
}