#pragma once
#include "Scene.h"
#include "GameObjectManager.h"
#include <vector>

// Components
#include "CameraComponent.h"
#include "DataContainer.h"

class MainMenu :
	public Scene
{
public:
	MainMenu();
	virtual ~MainMenu();

	virtual void Init() override;
};
