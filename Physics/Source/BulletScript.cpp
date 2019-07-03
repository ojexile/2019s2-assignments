#include "BulletScript.h"
#include "TransformComponent.h"


BulletScript::BulletScript()
{
	m_vDir = { 0,0,-1 };
}


BulletScript::~BulletScript()
{
}

void BulletScript::Update(double dt)
{
	GetComponent<TransformComponent>()->Translate({0,0,-10});
	CHENG_LOG("pos", std::to_string(GetComponent<TransformComponent>()->GetPosition().z));
}
void BulletScript::SetDirection(Vector3 vDir)
{
	m_vDir = vDir;
}