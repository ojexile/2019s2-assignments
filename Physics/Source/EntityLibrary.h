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
class EntityLibrary: public Singleton<EntityLibrary>
{
public:

	enum eEntities
	{
		FISH,
		COW,
		BIRD,
		CHICK,
		FOX,
		BOULDER,
		COVER,
		NUM_ENTITIES
	};

	enum eEnemies
	{
		MELEE,
		RANGED,
		NUM_ENEMIES
	};

	
	enum eEnvironment
	{
		STONE_1,
		STONE_2,
		GRASS_1,
		GRASS_2,
		NUM_ENVIRONMENT
	};


	enum eLoot
	{
		LOOT_CHEST,
		NUM_LOOT
	};

	EntityLibrary();
	virtual ~EntityLibrary();

	void Init();
	GameObject* GetEntity(eEntities type);
	GameObject** GetEntityArray();

	GameObject* GetEnemy(eEnemies type);
	GameObject** GetEnemyArray();

	GameObject* GetLoot(eLoot type);
	GameObject** GetLootArray();

	GameObject* GetEnvironment(eEnvironment type);
	GameObject** GetEnvironmentArray();

private:
	GameObject* m_EntityArray[NUM_ENTITIES];
	GameObject* m_EnemyArray[NUM_ENEMIES];
	GameObject* m_LootArray[NUM_LOOT];
	GameObject* m_EnvironmentArray[NUM_ENVIRONMENT];
};

