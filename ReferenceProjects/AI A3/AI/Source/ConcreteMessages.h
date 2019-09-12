#ifndef CONCRETE_MESSAGE_H
#define CONCRETE_MESSAGE_H

#include "Message.h"
#include "GameObject.h"

struct MessageWRU : public Message
{
	enum SEARCH_TYPE
	{
		SEARCH_NONE = 0,
		NEAREST_SHARK,
		NEAREST_FISHFOOD,
		NEAREST_FULLFISH,
		HIGHEST_ENERGYFISH,

		RANDOM_MINERAL,
		NEAREST_ENEMY,
		NEAREST_HARVESTER_REPAIRBOT,
		NEAREST_FRIENDLY_UNIT,
		RANDOM_DESTROYED_UNIT,
	};
	MessageWRU(GameObject *goValue, SEARCH_TYPE typeValue, float thresholdValue) : go(goValue), type(typeValue), threshold(thresholdValue) {}
	virtual ~MessageWRU() {}

	GameObject *go;
	SEARCH_TYPE type;
	float threshold;
};

struct MessageSendAll : public Message
{
	enum SEARCH_TYPE
	{
		CHECK_ACTIVE,
		CHECK_FISH,
		KILL_ALL,
	};
	MessageSendAll(GameObject *goValue, SEARCH_TYPE typeValue, float thresholdValue) : go(goValue), type(typeValue), threshold(thresholdValue) {}
	virtual ~MessageSendAll() {}

	GameObject *go;
	SEARCH_TYPE type;
	float threshold;
};

struct MessageSpawn : public Message
{
	enum SEARCH_TYPE
	{
		SPAWN_FOOD,
		SPAWN_FISH,
		SPAWN_ENEMYBULLET,
		SPAWN_FRIENDLYBULLET,
	};
	MessageSpawn(GameObject *goValue, SEARCH_TYPE typeValue) : go(goValue), type(typeValue){}
	virtual ~MessageSpawn() {}

	GameObject *go;
	SEARCH_TYPE type;
};

struct MessageStop : public Message
{
	enum SEARCH_TYPE
	{
		STOP_MOVING,
	};
	MessageStop(SEARCH_TYPE typeValue) : type(typeValue) {}
	virtual ~MessageStop() {}

	SEARCH_TYPE type;
};

struct MessageEvolve : public Message
{
	enum SEARCH_TYPE
	{
		EVOLVE,
	};
	MessageEvolve(GameObject *goValue, SEARCH_TYPE typeValue) : go(goValue), type(typeValue) {}
	virtual ~MessageEvolve() {}

	GameObject *go;
	SEARCH_TYPE type;
};

struct MessageDamage : public Message
{
	MessageDamage(GameObject *goValue) : go(goValue){}
	virtual ~MessageDamage() {}

	GameObject *go;
};

#endif
