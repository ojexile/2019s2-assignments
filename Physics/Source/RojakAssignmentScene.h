#pragma once
#include "Scene.h"
#include "GameObjectManager.h"
#include <vector>

// Components
#include "CameraComponent.h"
#include "DataContainer.h"

class RojakAssignmentScene :
	public Scene
{
public:
	RojakAssignmentScene();
	virtual ~RojakAssignmentScene();

	virtual void Init() override;
};
