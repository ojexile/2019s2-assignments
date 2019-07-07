#include "LightManager.h"



LightManager::LightManager()
{
	m_vec_SceneLights.push_back(new Light(Light::LIGHT_POINT));
	m_vec_SceneLights.push_back(new Light(Light::LIGHT_DIRECTIONAL));
	m_vec_SceneLights.push_back(new Light(Light::LIGHT_SPOT));
	m_currentLight = m_vec_SceneLights[0];
	m_iLightIndex = 0;
}
LightManager::~LightManager()
{
	for (int i = 0; i < m_vec_SceneLights.size(); ++i)
	{
		delete m_vec_SceneLights[i];
		m_vec_SceneLights[i] = nullptr;
	}
	m_currentLight = nullptr;
}
std::vector<Light*>& LightManager::GetSceneLights()
{
	return m_vec_SceneLights;
}
Light* LightManager::GetCurrentLight()
{
	return m_currentLight;
}
int LightManager::GetLightIndex()
{
	return m_iLightIndex;
}
void LightManager::CycleLight(bool b)
{
	//Cycle through the vector: true for forward, false for backward
	if (b)
	{
		if (m_currentLight == m_vec_SceneLights[SIZE - 1])
		{
			m_currentLight = m_vec_SceneLights[0];
			m_iLightIndex = 0;
		} 
		else
			++m_iLightIndex;
	}
	else
	{
		if (m_currentLight == m_vec_SceneLights[0])
		{
			m_currentLight = m_vec_SceneLights[SIZE - 1];
			m_iLightIndex = SIZE - 1;
		}
		else
			--m_iLightIndex;
	}
 	m_currentLight = m_vec_SceneLights[m_iLightIndex];

}
void LightManager::AdjustLightPower(float dt, bool b)
{
	if (b)
		m_currentLight->power = m_currentLight->power + dt;
	else
		m_currentLight->power = m_currentLight->power - dt;
}
void LightManager::AddLight(void)
{
	if (SIZE < MAX_NUMLIGHTS)
	{
		m_vec_SceneLights.push_back(new Light(Light::LIGHT_SPOT));
	}
}
void LightManager::RemoveLight(void)
{
	//pop from the back of the list
	if (SIZE > MIN_NUMLIGHTS)
	{
		--m_iLightIndex;
		if (m_currentLight == m_vec_SceneLights[SIZE - 1])
			m_currentLight = m_vec_SceneLights[m_iLightIndex];
		m_vec_SceneLights.pop_back(); 
	}
}