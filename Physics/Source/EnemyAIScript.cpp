#include "EnemyAIScript.h"
#include "ChengRigidbody.h"
#define MAX_HEALTH 100
EnemyAIScript::EnemyAIScript(GameObject* player)
{
	m_fHealth = MAX_HEALTH;
	m_Player = player;
}

EnemyAIScript::~EnemyAIScript()
{
}
void EnemyAIScript::Update(double dt)
{
	Movement();
	if (m_fHealth <= 0)
	{
		DestroySelf();
		return;
	}
	GetComponent<RenderComponent>()->SetColor({ m_fHealth / MAX_HEALTH,m_fHealth / MAX_HEALTH, m_fHealth / MAX_HEALTH });
}
void EnemyAIScript::Damage(float i)
{
	m_fHealth -= i;
}
void EnemyAIScript::Movement()
{
	const float speed = 25;
	// Dir
	Vector3 dir = m_Player->GetComponent<TransformComponent>()->GetPosition() - GetPosition();
	dir.y = 0;
	ChengRigidbody* rb = GetComponent<ChengRigidbody>();
	if (!rb)
		return;
	Vector3 pos = GetPosition();
	if (pos.x < 0 && pos.z > 0 || dir.x < 0 && dir.z > 0)
	{
		if (dir.Length() > 50)
			rb->SetVel(speed * dir.Normalize());
		else
			rb->SetVel({});
	}
	else
		rb->SetVel({});
}