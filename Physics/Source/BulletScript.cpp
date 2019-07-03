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
	GetComponent<TransformComponent>()->Translate(100 * (float)dt * m_vDir);
}
void BulletScript::SetDirection(Vector3 vDir)
{
	m_vDir = vDir;
}