#include "EntityLibrary.h"



EntityLibrary::EntityLibrary()
{
}


EntityLibrary::~EntityLibrary()
{

}

void EntityLibrary::Init()
{
	DataContainer* DC = DataContainer::GetInstance();
	
	//Entity Initialisation----------------------------------------------------
	m_EntityArray[FISH] = DC->GetGameObjectRaw("Fish");
	m_EntityArray[COW] = DC->GetGameObjectRaw("Cow");
	m_EntityArray[BIRD] = DC->GetGameObjectRaw("Bird");
	m_EntityArray[COVER] = DC->GetGameObjectRaw("Bird");
	m_EntityArray[FOX] = DC->GetGameObjectRaw("Fox");
	m_EntityArray[CHICK] = DC->GetGameObjectRaw("Chick");
	m_EntityArray[BOULDER] = DC->GetGameObjectRaw("boulder");

	//Enemy Initialisation----------------------------------------------------
	m_EnemyArray[MELEE] = DC->GetGameObjectRaw("Melee");
	m_EnemyArray[RANGED] = DC->GetGameObjectRaw("Ranged");

	//Loot Initialisation-----------------------------------------------------
	m_LootArray[LOOT_CHEST] = DC->GetGameObjectRaw("treasurebox");

	//Environmental Initialisation--------------------------------------------
	m_EnvironmentArray[STONE_1] = DC->GetGameObjectRaw("stone1");
	m_EnvironmentArray[STONE_2] = DC->GetGameObjectRaw("stone2");
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