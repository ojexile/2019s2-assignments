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
	GameObject* m_QuitButt;
	GameObject* m_QuitText;
	GameObject* m_TutorialText;
	GameObject* m_TutorialButt;

	float m_fPlayFadeVal;
public:
	MenuButtonsScript(GameObject* PlayText, GameObject* PlayButt,
		GameObject* QuitText, GameObject* QuitButt,
		GameObject* TutorialText, GameObject* TutorialButt);
	virtual ~MenuButtonsScript();
	virtual Component* Clone() { return new MenuButtonsScript(*this); };
	virtual void Update(double dt) override;
};
