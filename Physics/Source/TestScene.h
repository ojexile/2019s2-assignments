#pragma once
#include "Scene.h"

#include "GameObjectManager.h"

#include <vector>
class TestScene :
	public Scene
{
public:
	TestScene();
	virtual ~TestScene();

	virtual void Init();
};
