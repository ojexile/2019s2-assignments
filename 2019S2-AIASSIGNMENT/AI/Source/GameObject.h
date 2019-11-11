#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Vector3.h"
#include "StateMachine.h"
#include "ObjectBase.h"
#include <vector>

struct GameObject
{
	enum GAMEOBJECT_TYPE
	{
		GO_NONE = 0,
		GO_BALL,
		GO_CROSS,
		GO_CIRCLE,

		GO_FISH,
		GO_SHARK,
		GO_FISHFOOD,

		GO_ARMOREDSOLDIER,
		GO_HARVESTER,
		GO_MINERAL,
		GO_ENEMYAIRCRAFT,
		GO_REPAIRBOT,
		GO_ZERGLING,

		GO_ENEMYBULLET,
		GO_FRIENDLYBULLET,

		GO_TOTAL, //must be last
	};

	enum STATE
	{
		STATE_NONE = 0,
		STATE_TOOFULL,
		STATE_FULL,
		STATE_HUNGRY,
		STATE_DEAD,
	};
	GAMEOBJECT_TYPE type;
	Vector3 pos;
	Vector3 vel;
	Vector3 scale;
	bool active;
	float mass;
	Vector3 target;
	int id;
	int steps;

	float energy;
	float moveSpeed;
	float countDown;
	STATE currState;

	bool moveLeft, moveRight, moveUp, moveDown;

	StateMachine* sm;
	GameObject* bulletOwner;
	GameObject* targetGO;
	GameObject* targetMineral;
	Vector3 targetPos;
	int hp;
	bool carryingMineral;
	float lifetime;
	Vector3 prevPos;
	float repairTime;

	std::vector<Vector3> PatrolCheckpoints;
	int patrolCheckpointIndex;

	//Shark info
	GameObject* TargetFish;

	GameObject(GAMEOBJECT_TYPE typeValue = GO_BALL);
	~GameObject();

	void Update(double dt);
	bool Handle(Message *message);
};

#endif