#include "Application.h"

//Include GLEW
#include <GL/glew.h>

//Include GLFW
#include <GLFW/glfw3.h>

//Include the standard C++ headers
#include <stdio.h>
#include <stdlib.h>
#include "InputManager.h"
#include "Utility.h"
#include "Resources.h"


GLFWwindow* m_window;
const unsigned char FPS = 60; // FPS of this game
const unsigned int frameTime = 1000 / FPS; // time for each frame
static double scrollX = 0;
static double scrollY = 0;
int m_width, m_height;

//Define an error callback
static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
	_fgetchar();
}

//Define the key input callback
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

void resize_callback(GLFWwindow* window, int w, int h)
{
	m_width = w;
	m_height = h;
	glViewport(0, 0, w, h);
}

void scroll_callback(GLFWwindow* window, double dx, double dy)
{
	scrollX += dx;
	scrollY += dy;
}

bool Application::IsKeyPressed(unsigned short key)
{
	DEFAULT_LOG("IsKeyPressed(unsigned short) is deprecated");
	return ((GetAsyncKeyState(key) & 0x8001) != 0);
}
bool Application::IsMousePressed(unsigned short key) //0 - Left, 1 - Right, 2 - Middle
{
	return glfwGetMouseButton(m_window, key) != 0;
}
void Application::GetCursorPos(double* xpos, double* ypos)
{
	glfwGetCursorPos(m_window, xpos, ypos);
}
void Application::GetCursorPosRelative(double* xpos, double* ypos)
{
	double x, y;
	GetCursorPos(&x, &y);
	*xpos = x / Application::GetWindowWidth();
	*ypos = y / Application::GetWindowHeight();
}
void Application::GetScrollWheelPos(double* x, double* y)
{
	*x = scrollX;
	*y = scrollY;
}
int Application::GetWindowWidth()
{
	return m_width;
}
int Application::GetWindowHeight()
{
	return m_height;
}
void Application::SetCursorEnabled(bool b)
{
	// Camera
	if (b)
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	else
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}
Application::Application()
{
}

Application::~Application()
{
}

void Application::Init()
{
	//Set the error callback
	glfwSetErrorCallback(error_callback);

	//Initialize GLFW
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}

	//Set the GLFW window creation hints - these are optional
	glfwWindowHint(GLFW_SAMPLES, 4); //Request 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Request a specific OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //Request a specific OpenGL version
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL

	//Create a window and create its OpenGL context
	Vector3 WindowSize = StringToVector(Preferences::GetPref(Resources::PreferencesTerm::WindowSize));
	Vector3 WindowPos = StringToVector(Preferences::GetPref(Resources::PreferencesTerm::WindowPosition));
	m_width = (int)WindowSize.x;
	m_height = (int)WindowSize.y;
	m_window = glfwCreateWindow(m_width, m_height, "SP-Framework", NULL, NULL);
	glfwSetWindowPos(m_window, (int)WindowPos.x, (int)WindowPos.y);
	//If the window couldn't be created
	if (!m_window)
	{
		fprintf(stderr, "Failed to open GLFW window.\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//This function makes the context of the specified window current on the calling thread.
	glfwMakeContextCurrent(m_window);

	//Sets the key callback
	//glfwSetKeyCallback(m_window, key_callback);
	glfwSetWindowSizeCallback(m_window, resize_callback);
	glfwSetScrollCallback(m_window, scroll_callback);

	glewExperimental = true; // Needed for core profile
	//Initialize GLEW
	GLenum err = glewInit();

	//If GLEW hasn't initialized
	if (err != GLEW_OK)
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		//return -1;
	}

	// Engine
	m_Engine = new Engine;
	m_Engine->Init();
	m_Engine->SetMouseCallback(m_window);
}

void Application::Run()
{
	//Main Loop

	m_timer.startTimer();    // Start timer to calculate how long it takes to render this frame
	while (!glfwWindowShouldClose(m_window) && !InputManager::GetInstance()->GetInputStrength("ApplicationEscape"))
	{
		// Get delta time
		double dt = m_timer.getElapsedTime();
		// Run GameEngine
		m_Engine->Update(dt);
		//Swap buffers
		glfwSwapBuffers(m_window);
		//Get and organize events, like keyboard and mouse input, window resizing, etc...
		glfwPollEvents();
		m_timer.waitUntil(frameTime);       // Frame rate limiter. Limits each frame to a specified time in ms.
	} //Check if the ESC key had been pressed or if the window had been closed
	m_Engine->Exit();
}

void Application::Exit()
{
	//Close OpenGL window and terminate GLFW
	glfwDestroyWindow(m_window);
	//Finalize and clean up GLFW
	glfwTerminate();
	delete m_Engine;
}