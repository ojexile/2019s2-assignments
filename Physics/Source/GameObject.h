#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Vector3.h"

class GameObject
{
public:
	Vector3 m_vPosition;
	bool active;
public:
	GameObject();
	~GameObject();
};

#endif