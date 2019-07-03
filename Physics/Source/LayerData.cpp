#include "LayerData.h"



LayerData::LayerData(unsigned Shader)
	:m_Shader(Shader)
{
	m_vec_GameObjects = new std::vector<GameObject*>;
}


LayerData::~LayerData()
{
	for (auto p : *m_vec_GameObjects)
	{
		delete p;
	}
	m_vec_GameObjects->clear();
}
std::vector<GameObject*>* LayerData::GetGOList()
{
	return m_vec_GameObjects;
}
unsigned LayerData::GetShader()
{
	return m_Shader;
}