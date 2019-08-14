#include "UIButtonComponent.h"

#include "Application.h"

UIButtonComponent::UIButtonComponent()
{
}


UIButtonComponent::~UIButtonComponent()
{
}

void UIButtonComponent::Update(double dt)
{
	double x, y;
	Application::GetCursorPosRelative(&x, &y);
	Vector3 Pos = TRANS->GetPosition();
	Vector3 PosRel;
	PosRel.x = Pos.x / Application::GetWindowWidth();
	PosRel.y = Pos.y / Application::GetWindowHeight();
}