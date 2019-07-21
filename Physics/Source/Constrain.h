#pragma once
#include "ComponentBase.h"
#include "ComponentMacros.h"
class Constrain :
	public ComponentBase
{
public:
	enum eConstrainTypes
	{
		FIXED,		// lock x height to height map
		LIMIT,		// set lowest y val to height map
	};
private:
	_heightmap* m_Map;
	eConstrainTypes m_ConstrainType;
public:
	Constrain(_heightmap* map, eConstrainTypes type);
	virtual ~Constrain();
	virtual ComponentBase* Clone() { return new Constrain(*this); };
	virtual void Update(double dt) override;
};
