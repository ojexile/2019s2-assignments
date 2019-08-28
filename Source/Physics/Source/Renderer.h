#ifndef SCENE_H
#define SCENE_H

#include "Scene.h"
//Include GLEW
#include <GL/glew.h>

//Include GLFW
#include <GLFW/glfw3.h>

class Renderer
{
public:
	Renderer() {}
	virtual ~Renderer() {}

	virtual void Init() = 0;
	virtual void Update(double dt) = 0;
	virtual void Render(Scene* scene) = 0;
	virtual void Exit() = 0;

	virtual void SetMouseCallback(GLFWwindow* window) = 0; 

};

#endif