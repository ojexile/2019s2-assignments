#include "Entity_Library.h"



Entity_Library::Entity_Library()
{
}


Entity_Library::~Entity_Library()
{
}

void Entity_Library::Init()
{
	DataContainer* DO = DataContainer::GetInstance();
	
	//Entity Initialisation----------------------------------------------------
	m_EntityArray[FISH] = DO->GetGameObject("Fish");
	m_EntityArray[COW] = DO->GetGameObject("Cow");
	m_EntityArray[BOULDER] = DO->GetGameObject("boulder");
	m_EntityArray[COVER] = DO->GetGameObject("fliprock");
	
	//Enemy Initialisation----------------------------------------------------
	m_EnemyArray[MELEE] = DO->GetGameObject("Melee");
	m_EnemyArray[RANGED] = DO->GetGameObject("Ranged");

	//Loot Initialisation-----------------------------------------------------
	m_LootArray[LOOT_CHEST] = DO->GetGameObject("treasurebox");

}

GameObject* Entity_Library::GetEntity(eEntities type)
{
	return m_EntityArray[type];
}

GameObject** Entity_Library::GetEntityArray()
{
	return m_EntityArray;
}

GameObject* Entity_Library::GetEnemy(eEnemies type)
{
	return m_EnemyArray[type];
}

GameObject** Entity_Library::GetEnemyArray()
{
	return m_EnemyArray;
}

GameObject* Entity_Library::GetLoot(eLoot type)
{
	return m_LootArray[type];
}

GameObject** Entity_Library::GetLootArray()
{
	return m_LootArray;
}