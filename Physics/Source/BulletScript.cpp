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
	GetComponent<TransformComponent>()->Translate(m_vDir * 1 * dt);
}
void BulletScript::SetDirection(Vector3 vDir)
{
	m_vDir = vDir;
}