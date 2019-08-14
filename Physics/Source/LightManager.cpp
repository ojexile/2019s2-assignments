#include "LightManager.h"
//#include "Locator.h"
LightManager::LightManager()
{
	Light* directional = AddLight(Light::LIGHT_DIRECTIONAL);
	directional->position.Set(25, 30, 0);
	directional->power = 0.6f;
	/*m_currentLight = m_vec_SceneLights[0]:
	m_iLightIndex = 0;*/
}
LightManager::~LightManager()
{
	for (unsigned i = 0; i < m_vec_SceneLights.size(); ++i)
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
//void LightManager::CycleLight(bool b)
//{
//	//Cycle through the vector: true for forward, false for backward
//	if (b)
//	{
//		if (m_currentLight == m_vec_SceneLights[SIZE - 1])
//		{
//			m_currentLight = m_vec_SceneLights[0];
//			m_iLightIndex = 0;
//		}
//		else
//			++m_iLightIndex;
//	}
//	else
//	{
//		if (m_currentLight == m_vec_SceneLights[0])
//		{
//			m_currentLight = m_vec_SceneLights[SIZE - 1];
//			m_iLightIndex = SIZE - 1;
//		}
//		else
//			--m_iLightIndex;
//	}
//	if (m_iLightIndex < 0)
//		m_iLightIndex = 0;
//	m_currentLight = m_vec_SceneLights[m_iLightIndex];
//}
//void LightManager::AdjustLightPower(float dt, bool b)
//{
//	if (b)
//		m_currentLight->power = m_currentLight->power + dt;
//	else
//		m_currentLight->power = m_currentLight->power - dt;
//}
Light* LightManager::AddLight(Light::LIGHT_TYPE type)
{
	if (SIZE < MAX_NUMLIGHTS)
	{
		Light* L = new Light(type);
		L->position.Set(0, 0, 0);
		L->color.Set(1, 1, 1);
		L->power = 1;
		L->kC = 1.f;
		L->kL = 0.01f;
		L->kQ = 0.001f;
		L->cosCutoff = cos(Math::DegreeToRadian(45));
		L->cosInner = cos(Math::DegreeToRadian(30));
		L->exponent = 3.f;
		L->spotDirection.Set(0.f, 1.f, 0.f);
		m_vec_SceneLights.push_back(L);
		return L;
	}
	//DEFAULT_LOG("Max num lights reached. Unable to add light.");
	return nullptr;
}
void LightManager::RemoveLight(Light* light)
{
	////pop from the back of the list
	//if (SIZE > MIN_NUMLIGHTS)
	//{
	//	if (m_currentLight == m_vec_SceneLights[SIZE - 1])
	//		m_currentLight = m_vec_SceneLights[0];

	//	delete m_vec_SceneLights[SIZE - 1];
	//	m_vec_SceneLights[SIZE - 1] = nullptr;
	//	m_vec_SceneLights.pop_back();
	//	--m_iLightIndex;
	//}
}