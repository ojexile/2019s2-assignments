#pragma once
#include "Singleton.h"
#include "DataContainer.h"
/********************************************************************************/
/*!
\author Ryan Tan Zheng Rong
\brief
Container that contains all entities in an array. Associated with Chunk events
as the events require data on what kind of entities to spawn
/*!
/********************************************************************************/
class Entity_Library: public Singleton<Entity_Library>
{
public:

	enum eEntities
	{
		FISH,
		COW,
		BOULDER,
		COVER,
		NUM_ENTITIES
	};

	Entity_Library();
	~Entity_Library();

	void Init();
	GameObject* getEntity(eEntities type);
	GameObject** getArray();
private:
	GameObject* m_EntityArray[NUM_ENTITIES];
};

