#include "UIButtonComponent.h"

#include "Application.h"

UIButtonComponent::UIButtonComponent()
{
	m_bIsHover = false;
}


UIButtonComponent::~UIButtonComponent()
{
}

void UIButtonComponent::Update(double dt)
{
	double x, y;
	Application::GetCursorPosRelative(&x, &y);
	Vector3 MousePos((float)x, (float)y, 0);
	Vector3 Pos = TRANS->GetPosition();
	Vector3 PosRel;
	PosRel.x = Pos.x / 1920;
	PosRel.y = Pos.y / 1080;
	Vector3 vScaleRel;
	vScaleRel.x = TRANS->GetScale().x / Application::GetWindowWidth();
	vScaleRel.y = TRANS->GetScale().y / Application::GetWindowHeight();
	// Check collision
	 Vector3 vMin = PosRel - vScaleRel * 0.5f;
	 Vector3 vMax = PosRel + vScaleRel * 0.5f;
	 if (MousePos.x >= vMin.x && MousePos.y >= vMin.y)
	 {
		 if (MousePos.x <= vMax.x && MousePos.y <= vMax.y)
		 {
			 m_bIsHover = true;
		 }
		 else
			 m_bIsHover = false;
	 }
	 else
		 m_bIsHover = false;
}