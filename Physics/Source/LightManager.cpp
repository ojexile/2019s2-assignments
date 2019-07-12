#include "LightManager.h"

LightManager::LightManager()
{
	m_vec_SceneLights.push_back(new Light(Light::LIGHT_POINT));
	m_vec_SceneLights.push_back(new Light(Light::LIGHT_DIRECTIONAL));
	m_vec_SceneLights.push_back(new Light(Light::LIGHT_SPOT));

	m_vec_PlayerLights.push_back(new Light(Light::LIGHT_POINT));
	m_vec_PlayerLights.push_back(new Light(Light::LIGHT_DIRECTIONAL));
	m_vec_PlayerLights.push_back(new Light(Light::LIGHT_SPOT));
}
LightManager::~LightManager()
{
	for (unsigned i = 0; i < m_vec_PlayerLights.size(); ++i)
	{
		delete m_vec_PlayerLights[i];
		m_vec_PlayerLights[i] = nullptr;
	}
	for (unsigned i = 0; i < m_vec_SceneLights.size(); ++i)
	{
		delete m_vec_SceneLights[i];
		m_vec_SceneLights[i] = nullptr;
	}
}
std::vector<Light*>& LightManager::GetSceneLights()
{
	return m_vec_SceneLights;
}