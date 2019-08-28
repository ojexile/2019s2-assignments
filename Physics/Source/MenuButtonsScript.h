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
	GameObject* m_TutorialBox;
	GameObject* m_Ability0;
	GameObject* m_Ability1;
	GameObject* m_Ability2;
	GameObject* m_Ability3;

	float m_fPlayFadeVal;
	float m_fTutorialFadeVal;
	float m_fQuitFadeVal;
public:
	MenuButtonsScript(GameObject* PlayText, GameObject* PlayButt,
		GameObject* QuitText, GameObject* QuitButt,
		GameObject* TutorialText, GameObject* TutorialButt,
		GameObject* TutorialBox, GameObject* Ability0,
		GameObject* Ability1, GameObject* Ability2, GameObject* Ability3);
	virtual void Start() override;
	virtual ~MenuButtonsScript();
	virtual Component* Clone() { return new MenuButtonsScript(*this); };
	virtual void Update(double dt) override;
};
