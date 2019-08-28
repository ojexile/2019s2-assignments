#include "UIButtonComponent.h"

#include "Application.h"

UIButtonComponent::UIButtonComponent()
{
	m_bIsHover = false;
}

UIButtonComponent::~UIButtonComponent()
{
}

void UIButtonComponent::Start()
{
	this->GetGO()->SetDisableDistance(-1);
}

void UIButtonComponent::Update(double dt)
{
	double x, y;
	Application::GetCursorPosRelative(&x, &y);
	Vector3 MousePos((float)x, (float)y, 0);
	Vector3 Pos = TRANS->GetPosition();
	Vector3 PosRel;
	PosRel.x = Pos.x / 1920;
	PosRel.y = (1080 - Pos.y) / 1080;	// Flip y axis
	Vector3 vScaleRel;
	vScaleRel.x = TRANS->GetScale().x / Application::GetWindowWidth();
	vScaleRel.y = TRANS->GetScale().y / Application::GetWindowHeight();
	// Check collision
	Vector3 vMin = PosRel - vScaleRel * 0.5f;
	Vector3 vMax = PosRel + vScaleRel * 0.5f;
	//CHENG_LOG("Min: ", VectorToString(vMin));
	//CHENG_LOG("Mouse: ", VectorToString(MousePos));
	//CHENG_LOG("Max: ", VectorToString(vMax));
	if (MousePos.x >= vMin.x && MousePos.y >= vMin.y)
	{
		if (MousePos.x <= vMax.x && MousePos.y <= vMax.y)
		{
			m_bIsHover = true;
			SceneManager::GetInstance()->GetScene()->SetCursorEnabled(true);
		}
		else
			m_bIsHover = false;
	}
	else
		m_bIsHover = false;
	//if (m_bIsHover)
	//	CHENG_LOG("Coll", "YES");
	//else
	//	CHENG_LOG("Coll", "NO");
}
bool UIButtonComponent::GetHover()
{
	return m_bIsHover;
}