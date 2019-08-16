#include "MouseManager.h"
#include "Application.h"

MouseManager::MouseManager()
{
	lastX = 0; lastY = 0; lastScrollX = 0; lastScrollY = 0;
}

float MouseManager::GetStrength(std::string bind)
{
	if (bind == "lmb")
	{
		return (Application::IsMousePressed(0) ? 1 : 0);
	}
	if (bind == "rmb")
	{
		return (Application::IsMousePressed(1) ? 1 : 0);
	}
	if (bind == "mmb")
	{
		return (Application::IsMousePressed(2) ? 1 : 0);
	}
	if (bind == "lmb_down")
	{
		bool result = !lastLMB && Application::IsMousePressed(0);
		lastLMB = Application::IsMousePressed(0);
		return ( result ? 1 : 0);
	}
	if (bind == "rmb_down")
	{
		bool result = !lastRMB  && Application::IsMousePressed(1);
		lastRMB = Application::IsMousePressed(1);
		return (result ? 1 : 0);
	}
	if (bind == "mmb")
	{
		return (Application::IsMousePressed(2) ? 1 : 0);
	}
	if (bind == "x")
	{
		double xpos, ypos;
		Application::GetCursorPos(&xpos, &ypos);
		float rVal = lastX - xpos;
		lastX = xpos;
		return rVal;
	}
	if (bind == "y")
	{
		double xpos, ypos;
		Application::GetCursorPos(&xpos, &ypos);
		float rVal = lastY - ypos;
		lastY = ypos;
		return rVal;
	}
	if (bind == "scroll")
	{
		double scrollx, scrolly;
		Application::GetScrollWheelPos(&scrollx, &scrolly);
		float rVal = lastScrollY - scrolly;
		lastScrollY = scrolly;
		return rVal;
		
	}
}

