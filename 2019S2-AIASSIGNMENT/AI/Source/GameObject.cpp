#include "GameObject.h"
#include "ConcreteMessages.h"

GameObject::GameObject(GAMEOBJECT_TYPE typeValue) 
	: type(typeValue),
	scale(1, 1, 1),
	active(false),
	mass(1.f),
	sm(NULL),
	TargetFish(NULL),
	targetGO(NULL),
	targetMineral(NULL),
	bulletOwner(NULL),
	hp(0),
	lifetime(0),
	patrolCheckpointIndex(-1),
	repairTime(0),
	carryingMineral(false)
{
	moveLeft = moveRight = moveUp = moveDown = true;
}

GameObject::~GameObject()
{
	if (sm)
	{
		delete sm;
		sm = NULL;
	}
}

void GameObject::Update(double dt)
{
	sm->Update(dt);
}

bool GameObject::Handle(Message *message)
{
	MessageSendAll *messageSendAll = dynamic_cast<MessageSendAll*>(message);
	if (messageSendAll)
	{
		switch (messageSendAll->type)
		{
		case MessageSendAll::CHECK_ACTIVE:
			if (active == true)
			{
				delete message;
				return true;
			}
			break;
		case MessageSendAll::CHECK_FISH:
			if (type == GO_FISH && active == true)
			{
				delete message;
				return true;
			}
			break;
		case MessageSendAll::KILL_ALL:
			if (active == true && type == GO_ENEMY)
			{
				active = false;
				delete message;
				return true;
			}
			break;
		}
	}

	MessageStop *messageStop = dynamic_cast<MessageStop*>(message);
	if (messageStop)
	{
		switch (messageStop->type)
		{
		case MessageStop::STOP_MOVING:
			if(this)
				moveSpeed = 0;

			return true;
			break;
		}
	}

	delete message;
	return false;
}