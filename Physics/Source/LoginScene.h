#pragma once
#include "Scene.h"
class LoginScene :
	public Scene
{
public:
	LoginScene();
	virtual ~LoginScene();

	virtual void Init() override;
};
