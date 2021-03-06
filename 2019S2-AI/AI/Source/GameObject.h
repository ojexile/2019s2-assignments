#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Vector3.h"
#include "StateMachine.h"
#include "NeuralNode.h"
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

		GO_PIPE,
		GO_BIRD,
		GO_NPC,

		GO_TOTAL, //must be last
	};

	enum STATE
	{
		STATE_NONE = 0,
		STATE_TOOFULL, 
		STATE_FULL,
		STATE_HUNGRY,
		STATE_DEAD
	}; 

	float energy;
	float moveSpeed;
	float countDown;


	GAMEOBJECT_TYPE type;
	Vector3 pos;
	Vector3 vel;
	Vector3 scale;
	bool active;
	float mass;
	Vector3 target;
	int id;
	int steps;

	bool alive;
	int score;
	std::vector<NeuralNode> hiddenNode;
	NeuralNode outputNode;


	Vector3 targetLocation;



	GameObject(GAMEOBJECT_TYPE typeValue = GO_BALL);
	~GameObject();

	//states in gameobject
	STATE currState;
	StateMachine* sm;
	void Update(double dt);

};

#endif