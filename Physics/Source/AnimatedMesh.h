#pragma once
#include "Animation.h"
#include "Mesh.h"
#include <Windows.h>
#include <string>
#include "Vertex.h"
#include "Mtx44.h"
#include "MatrixStack.h"
#include "Material.h"

#include "GL/glew.h"
#include "GLFW/glfw3.h"

class AnimatedMesh : public Mesh
{
public:
public:
	AnimatedMesh(std::string sMeshName, int row, int col);
	~AnimatedMesh();
	virtual void Update(double dt) override;
	virtual void Render(bool bEnabledLight); // Polymorphism
	int m_row;
	int m_col;
	float m_currentTime;
	int m_currentFrame;
	int m_playCount;
	Animation *m_anim;
};
