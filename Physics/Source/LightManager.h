#pragma once
#include "Light.h"
#include <vector>
class LightManager
{
private:
	std::vector<Light*> m_vec_SceneLights;
	std::vector<Light*> m_vec_PlayerLights;

public:
	LightManager();
	~LightManager();

	//Get a reference to scene lights
	std::vector<Light*>& GetSceneLights();

};

