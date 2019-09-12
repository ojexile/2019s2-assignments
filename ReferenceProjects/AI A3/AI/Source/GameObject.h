#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Vector3.h"
#include "StateMachine.h"
#include "ObjectBase.h"
#include "Maze.h"
#include "Graph.h"
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

		GO_ORAN_BERRY,
		GO_KEY,
		GO_MONSTER_BULBASAUR,
		GO_MONSTER_ABSOL,
		GO_MONSTER_FLYGON,
		GO_PLAYER,

		GO_NPC,
		GO_TOWER,
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
	float countDown;
	STATE currState;

	bool moveLeft, moveRight, moveUp, moveDown;

	StateMachine* sm;
	GameObject* bulletOwner;
	GameObject* targetMineral;
	Vector3 targetPos;
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

	//Assignment 2
	void Update(double dt);
	bool Handle(Message *message);

	std::vector<Maze::TILE_CONTENT> grid;
	std::vector<bool> visited;
	std::vector<MazePt> stack;
	std::vector<MazePt> path;
	std::vector<MazePt> previous;
	MazePt curr;
	MazePt prev;

	bool mapReadFinished;
	MazePt mazeTargetPos;
	float targetDist;
	int cost;
	
	Maze::DIRECTION attackDir;
	int oranBerryCount;
	bool objectLeft, objectRight, objectUp, objectDown;

	Node* currNode;
	Node* prevNode;
	std::vector<Node*> gStack;

	enum FACTIONS
	{
		FACTION_BLUE,
		FACTION_RED,
		FACTION_NEUTRAL,
		FACTION_TOTAL
	};

	std::vector<Node*> gPath;
	FACTIONS faction;
	float range;
	float attackSpeed;
	int currentPathIndex;
	int previousPathIndex;
	bool towerDestroyed;
	int moveSpeed;
	int damage;
	GameObject* targetGO;
	int maxHp;
	int hp;
};

#endif