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
	Vector3 posOG = trans->GetPosition();
	Vector3 pos = trans->GetPosition();
	pos -= m_Data->GetPos();
	Vector3 terrainPos = { pos.x, Scale.y * ReadHeightMap(*heightMap, pos.x / Scale.x, pos.z / Scale.z), pos.z };
	terrainPos.y -= 0.4f * Scale.y;
	terrainPos.y += m_Data->GetPos().y;
	switch (m_ConstrainType)
	{
	case Constrain::FIXED:
		trans->SetPosition(posOG.x, terrainPos.y, posOG.z);
		break;
	case Constrain::LIMIT:
		if (pos.y < terrainPos.y)
			trans->SetPosition(posOG.x, terrainPos.y, posOG.z);
		break;
	default:
		break;
	}
}
void Constrain::SetHeightMapData(HeightMapData* data)
{
	m_Data = data;
}