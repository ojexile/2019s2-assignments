#include "EntityLibrary.h"



EntityLibrary::EntityLibrary()
{
}


EntityLibrary::~EntityLibrary()
{
	for (unsigned i = 0; i < NUM_ENTITIES; ++i)
	{
		delete m_EntityArray[i];
		m_EntityArray[i] = nullptr;
	}
	delete[] m_EntityArray;

	for (unsigned i = 0; i < NUM_ENEMIES; ++i)
	{
		delete m_EnemyArray[i];
		m_EnemyArray[i] = nullptr;
	}
	delete[] m_EnemyArray;
	
	for (unsigned i = 0; i < NUM_ENVIRONMENT; ++i)
	{
		delete m_EnvironmentArray[i];
		m_EnvironmentArray[i] = nullptr;
	}
	delete[] m_EnvironmentArray;

	for (unsigned i = 0; i < NUM_LOOT; ++i)
	{
		delete m_LootArray[i];
		m_LootArray[i] = nullptr;
	}

	delete[] m_LootArray;
}

void EntityLibrary::Init()
{
	DataContainer* DC = DataContainer::GetInstance();
	
	//Entity Initialisation----------------------------------------------------
	m_EntityArray[FISH] = DC->GetGameObject("Fish");
	m_EntityArray[COW] = DC->GetGameObject("Cow");
	m_EntityArray[BIRD] = DC->GetGameObject("Bird");
	m_EntityArray[COVER] = DC->GetGameObject("Bird");
	m_EntityArray[FOX] = DC->GetGameObject("Fox");
	m_EntityArray[CHICK] = DC->GetGameObject("Chick");
	m_EntityArray[BOULDER] = DC->GetGameObject("boulder");

	//Enemy Initialisation----------------------------------------------------
	m_EnemyArray[MELEE] = DC->GetGameObject("Melee");
	m_EnemyArray[RANGED] = DC->GetGameObject("Ranged");

	//Loot Initialisation-----------------------------------------------------
	m_LootArray[LOOT_CHEST] = DC->GetGameObject("treasurebox");

	//Environmental Initialisation--------------------------------------------
	m_EnvironmentArray[STONE_1] = DC->GetGameObject("stone1");
	m_EnvironmentArray[STONE_2] = DC->GetGameObject("stone2");
	m_EnvironmentArray[GRASS_1] = DC->GetGameObject("grass1");
	m_EnvironmentArray[GRASS_2] = DC->GetGameObject("grass2");
}

GameObject* EntityLibrary::GetEntity(eEntities type)
{
	return m_EntityArray[type];
}

GameObject** EntityLibrary::GetEntityArray()
{
	return m_EntityArray;
}

GameObject* EntityLibrary::GetEnemy(eEnemies type)
{
	return m_EnemyArray[type];
}

GameObject** EntityLibrary::GetEnemyArray()
{
	return m_EnemyArray;
}

GameObject* EntityLibrary::GetLoot(eLoot type)
{
	return m_LootArray[type];
}

GameObject** EntityLibrary::GetLootArray()
{
	return m_LootArray;
}

GameObject* EntityLibrary::GetEnvironment(eEnvironment type)
{
	return m_EnvironmentArray[type];
}

GameObject** EntityLibrary::GetEnvironmentArray()
{
	return m_EnvironmentArray;
}