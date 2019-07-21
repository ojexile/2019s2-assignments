#include "Constrain.h"

Constrain::Constrain(heightmap& map, eConstrainTypes type)
	: m_Map(map)
	, m_ConstrainType(type)
{
}

Constrain::~Constrain()
{
}

void Constrain::Update(double dt)
{
	switch (m_ConstrainType)
	{
	case Constrain::FIXED:
		trans->SetPosition(pos.x, 30.f * ReadHeightMap(DataContainer::GetInstance()->heightMap, pos.x / 500, pos.z / 500), pos.z);
		break;
	case Constrain::LIMIT:
		break;
	default:
		break;
	}
}