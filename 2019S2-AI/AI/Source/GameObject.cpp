
#include "GameObject.h"

GameObject::GameObject(GAMEOBJECT_TYPE typeValue)
	: type(typeValue),
	scale(1, 1, 1),
	active(false),
	mass(1.f),
	currState(STATE_NONE),
	energy(0.f),
	countDown(0.f)
{
}

GameObject::~GameObject()
{
}