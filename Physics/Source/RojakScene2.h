#pragma once
#include "Scene.h"
#include "GameObjectManager.h"
#include <vector>

// Components
#include "CameraComponent.h"
#include "DataContainer.h"

class RojakScene2 :
	public Scene
{
public:
	RojakScene2();
	virtual ~RojakScene2();

	virtual void Init() override;
};
