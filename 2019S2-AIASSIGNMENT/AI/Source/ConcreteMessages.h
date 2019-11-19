#ifndef CONCRETE_MESSAGE_H
#define CONCRETE_MESSAGE_H

#include "Message.h"
#include "GameObject.h"

struct MessageWRU : public Message
{
	enum SEARCH_TYPE
	{
		SEARCH_NONE = 0,

		RANDOM_MINERAL,
		NEAREST_ENEMY,
		NEAREST_HARVESTER_REPAIRER,
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

#endif
