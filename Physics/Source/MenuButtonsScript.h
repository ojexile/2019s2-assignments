#pragma once
#include "ScriptComponent.h"
/********************************************************************************/
/*!
\author Hao Cheng
\brief
Provide functionality and visual effects for buttons on menu screen.
/*!
/********************************************************************************/
class MenuButtonsScript :
	public ScriptComponent
{
private:
	GameObject* m_PlayText;
	GameObject* m_PlayButt;
public:
	MenuButtonsScript(GameObject* PlayText, GameObject* PlayButt);
	virtual ~MenuButtonsScript();
	virtual Component* Clone() { return new MenuButtonsScript(*this); };
	virtual void Update(double dt) override;
};
