#pragma once
#include "Scene.h"
#include "GameObjectManager.h"
#include <vector>

// Components
#include "CameraComponent.h"
#include "DataContainer.h"

class ChengAssignmentScene :
	public Scene
{
public:
	ChengAssignmentScene();
	virtual ~ChengAssignmentScene();

	virtual void Init() override;
};
