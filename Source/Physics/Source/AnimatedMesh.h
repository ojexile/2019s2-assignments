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

class AnimatedMesh
{
public:
public:
	AnimatedMesh(std::string sMeshName, int row, int col, int start, int end, float time, bool loop, Mesh* mesh);
	AnimatedMesh(AnimatedMesh& ref);
	virtual ~AnimatedMesh();
	virtual void Update(double dt);
	virtual void Render(); // Polymorphism

	bool m_bOriginal;
	Mesh* m_Mesh;
	int m_row;
	int m_col;
	float m_currentTime;
	int m_currentFrame;

	Animation m_anim;
};
