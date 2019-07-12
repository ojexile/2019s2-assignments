#include "ChengRigidbody.h"
#include "TransformComponent.h"
ChengRigidbody::ChengRigidbody()
{
	m_eType = BALL;
	m_fMass = 1;
}

ChengRigidbody::~ChengRigidbody()
{
}
void ChengRigidbody::Update(double dt)
{
	TransformComponent* Trans = this->GetComponent<TransformComponent>();
	Trans->Translate(m_vVel * (float)dt);
}
void ChengRigidbody::SetVel(Vector3 v)
{
	this->m_vVel = v;
}