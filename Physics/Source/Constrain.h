#pragma once
#include "ComponentBase.h"
#include "ComponentMacros.h"
#include "HeightMapData.h"
class Constrain :
	public Component
{
public:
	enum eConstrainTypes
	{
		FIXED,		// lock x height to height map
		LIMIT,		// set lowest y val to height map
	};
private:
	HeightMapData* m_Data;
	eConstrainTypes m_ConstrainType;
public:
	Constrain(HeightMapData*, eConstrainTypes type);
	virtual ~Constrain();
	virtual Component* Clone() { return new Constrain(*this); };
	virtual void Update(double dt) override;

	void SetHeightMapData(HeightMapData* data);
};
