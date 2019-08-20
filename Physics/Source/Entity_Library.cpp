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
	m_EntityArray[FISH] = DO->GetGameObject("Fish");

}

GameObject* Entity_Library::getEntity(eEntities type)
{
	return m_EntityArray[type];
}

GameObject** Entity_Library::getArray()
{
	return m_EntityArray;
}