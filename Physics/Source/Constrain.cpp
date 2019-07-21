#include "Constrain.h"
#include "LoadHmap.h"
#include "TransformComponent.h"
Constrain::Constrain(HeightMapData* data, eConstrainTypes type)
	: m_Data(data)
	, m_ConstrainType(type)
{
}

Constrain::~Constrain()
{
}

void Constrain::Update(double dt)
{
	TransformComponent* trans = TRANS;
	Vector3 Scale = m_Data->GetScale();
	_heightmap* heightMap = m_Data->GetHeightMap();
	Vector3 pos = trans->GetPosition();
	Vector3 terrainPos = { pos.x, Scale.y * ReadHeightMap(*heightMap, pos.x / Scale.x, pos.z / Scale.z), pos.z };
	terrainPos.y -= 0.6f * Scale.y;
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