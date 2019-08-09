#pragma once
#include "Scene.h"
#include "GameObjectManager.h"
#include <vector>

// Components
#include "CameraComponent.h"
#include "DataContainer.h"

class DefaultScene :
	public Scene
{
public:
	DefaultScene();
	virtual ~DefaultScene();

	virtual void Init() override;
};
