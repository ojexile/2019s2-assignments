#pragma once
#include "GameObject.h"
#include <vector>
class LayerData
{
private:
	std::vector<GameObject*>* m_vec_GameObjects;
	unsigned m_Shader;
public:
	LayerData(unsigned Shader);
	~LayerData();

	std::vector<GameObject*>* GetGOList();
	unsigned GetShader();
};

