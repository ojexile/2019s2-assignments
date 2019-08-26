#pragma once
#include "Scene.h"
class MainMenu :
	public Scene
{
public:
	MainMenu();
	virtual ~MainMenu();

	virtual void Init() override;
};
