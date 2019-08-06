#include "EnemyAIScript.h"
#include "ChengRigidbody.h"
#include "GunScript.h"
#define MAX_HEALTH 100
EnemyAIScript::EnemyAIScript(GameObject* player, GameObject* gun)
	:m_Gun(gun)
{
	m_fHealth = MAX_HEALTH;
	m_Player = player;
}

EnemyAIScript::~EnemyAIScript()
{
}
void EnemyAIScript::Update(double dt)
{
	Movement(dt);
	if (m_fHealth <= 0)
	{
		Destroy(m_Gun);
		DestroySelf();
		return;
	}
	GetComponent<RenderComponent>()->SetColor({ m_fHealth / MAX_HEALTH,m_fHealth / MAX_HEALTH, m_fHealth / MAX_HEALTH });
}
void EnemyAIScript::Damage(float i)
{
	m_fHealth -= i;
}
void EnemyAIScript::Movement(double dt)
{
	const float speed = 12;
	// Dir
	Vector3 dir = m_Player->GetComponent<TransformComponent>()->GetPosition() - GetPosition();
	// dir.y += 5; // offset for player height
	m_Gun->TRANS->SetPosition(GetPosition());
	m_Gun->TRANS->Translate({ 0,4,0 });
	m_Gun->TRANS->Translate(dir.Normalized() * 4);
	ChengRigidbody* rb = GetComponent<ChengRigidbody>();
	if (!rb)
		return;
	Vector3 pos = GetPosition();
	if (pos.x < 0 && pos.z > 0 || dir.x < 0 && dir.z > 0)
	{
		if (dir.Length() > 100)
			rb->SetVel({});
		if (dir.Length() > 50)
			rb->SetVel(speed * dir.Normalized());
		else
		{
			rb->SetVel({});
			m_Gun->GetComponent<GunScript>()->PullTrigger(dir.Normalized(), dt);
			if (m_Gun->GetComponent<GunScript>()->IsEmpty())
				m_Gun->GetComponent<GunScript>()->Reload();
		}
	}
	else
		rb->SetVel({});
}