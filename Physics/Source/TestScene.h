#pragma once
#include "Scene.h"
#include "GameObjectManager.h"
#include <vector>

// Components
#include "CameraComponent.h"
#include "DataContainer.h"

class TestScene :
	public Scene
{
public:
	TestScene();
	virtual ~TestScene();

	virtual void Init() override;
};
