
#include "GameObject.h"

GameObject::GameObject(GAMEOBJECT_TYPE typeValue)
	: type(typeValue),
	scale(1, 1, 1),
	active(false),
	mass(1.f),
	currState(STATE_NONE),
	energy(0.f),
	countDown(-1.f),
	sm(NULL)
{
}

GameObject::~GameObject()
{
	if (sm != nullptr)
		delete sm;
}

void GameObject::Update(double dt)
{
	switch (this->currState)
	{
	case GameObject::STATE_TOOFULL:
		this->energy -= dt;
		this->moveSpeed = 0;
		if (this->energy < 10)
		{
			this->currState = STATE_FULL;
		}
		break;
	case GameObject::STATE_FULL:
		this->energy -= dt;
		this->moveSpeed = 2;
		if (this->energy >= 10)
		{
			this->currState = STATE_TOOFULL;
			//overfull++;
		}
		else if (this->energy < 5)
		{
			this->currState = STATE_HUNGRY;
		}
		break;
	case GameObject::STATE_HUNGRY:
		this->energy -= dt;
		this->moveSpeed = 1;
		if (this->energy >= 5)
		{
			this->currState = STATE_FULL;
		}
		else if (this->energy <= 0)
		{
			if (this->energy > -1)
			{
				//deathByHunger++;
			}
			this->currState = STATE_DEAD;
			this->countDown = 3;
		}
		break;
	case GameObject::STATE_DEAD:
		this->moveSpeed = 0;
		this->countDown -= dt;

		if (this->countDown <= 0)
		{
			this->active = false;
			//m_objectCount--;
		}
		break;
	}
}
