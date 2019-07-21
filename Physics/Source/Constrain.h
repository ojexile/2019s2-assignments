#pragma once
#include "ComponentBase.h"
#include "ComponentMacros.h"
class Constrain :
	public ComponentBase
{
	enum eConstrainTypes
	{
		FIXED,		// lock x height to height map
		LIMIT,		// set lowest y val to height map
	};
private:
	const heightmap m_Map;
	eConstrainTypes m_ConstrainType;
public:
	Constrain(heightmap& map, eConstrainTypes type);
	virtual ~Constrain();

	virtual void Update(double dt) override;
};
