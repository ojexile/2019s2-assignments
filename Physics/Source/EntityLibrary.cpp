#include "EntityLibrary.h"



EntityLibrary::EntityLibrary()
{
}


EntityLibrary::~EntityLibrary()
{
}

void EntityLibrary::Init()
{
	DataContainer* DO = DataContainer::GetInstance();
	
	//Entity Initialisation----------------------------------------------------
	m_EntityArray[FISH] = DO->GetGameObject("Fish");
	m_EntityArray[COW] = DO->GetGameObject("Cow");
	m_EntityArray[BIRD] = DO->GetGameObject("Bird");
	m_EntityArray[COVER] = DO->GetGameObject("Bird");
	m_EntityArray[BOULDER] = DO->GetGameObject("boulder");

	//Enemy Initialisation----------------------------------------------------
	m_EnemyArray[MELEE] = DO->GetGameObject("Melee");
	m_EnemyArray[RANGED] = DO->GetGameObject("Ranged");

	//Loot Initialisation-----------------------------------------------------
	m_LootArray[LOOT_CHEST] = DO->GetGameObject("treasurebox");

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