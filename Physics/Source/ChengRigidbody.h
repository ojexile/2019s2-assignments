#pragma once
#include "ComponentBase.h"
class ChengRigidbody :
	public ComponentBase
{
public:
	enum ePhysicsTypes
	{
		BALL,
		WALL,
		PILLAR,
	};
private:

public:
	ChengRigidbody();
	virtual ~ChengRigidbody();
	virtual ComponentBase* Clone()
	{
		return new ChengRigidbody(*this);
	}
};
