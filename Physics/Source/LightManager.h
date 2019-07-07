#pragma once
#include "Light.h"
#include <vector>

#define SIZE m_vec_SceneLights.size()
#define MAX_NUMLIGHTS 5

class LightManager
{
private:
	//Default: 3 types of light in vector
	std::vector<Light*> m_vec_SceneLights;
	Light* m_currentLight;
	int m_iLightIndex;
public:
	LightManager();
	~LightManager();

	//Get a guranteed reference to scene lights
	std::vector<Light*>& GetSceneLights();
	Light* GetCurrentLight();
	int GetLightIndex();

	void AdjustLightPower(float dt, bool);
	
	void CycleLight(bool);
	
	void AddLight();
	void RemoveLight();

};

