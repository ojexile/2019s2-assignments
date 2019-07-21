#include "Constrain.h"
#include "LoadHmap.h"
#include "TransformComponent.h"
Constrain::Constrain(_heightmap* map, eConstrainTypes type)
	: m_Map(map)
	, m_ConstrainType(type)
{
}

Constrain::~Constrain()
{
}

void Constrain::Update(double dt)
{
	TransformComponent* trans = TRANS;
	Vector3 pos = trans->GetPosition();
	Vector3 terrainPos = { pos.x, 30.f * ReadHeightMap(*m_Map, pos.x / 500, pos.z / 500), pos.z };
	switch (m_ConstrainType)
	{
	case Constrain::FIXED:
		trans->SetPosition(terrainPos);
		break;
	case Constrain::LIMIT:
		if (pos.y < terrainPos.y)
			trans->SetPosition(terrainPos);
		break;
	default:
		break;
	}
}