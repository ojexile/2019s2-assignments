#pragma once
#include "Scene.h"
#include "GameObjectManager.h"
#include <vector>

// Components
#include "CameraComponent.h"
#include "DataContainer.h"

class ChengPhysicsScene :
	public Scene
{
public:
	ChengPhysicsScene();
	virtual ~ChengPhysicsScene();

	virtual void Init() override;
};
