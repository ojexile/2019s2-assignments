#pragma once
#include "ScriptComponent.h"
/********************************************************************************/
/*!
\author Hao Cheng
\brief
Functaionality of login buttons
/*!
/********************************************************************************/
class LoginButtonScript :
	public ScriptComponent
{
private:
	GameObject* m_User;
	GameObject* m_Pass;
	GameObject* m_LoginLocal;
	GameObject* m_CreateLocal;
	GameObject* m_LoginGO;
public:
	LoginButtonScript(GameObject* LoginGO, GameObject* LoginLocal, GameObject* CreateLocal);
	virtual ~LoginButtonScript();
	virtual void Update(double dt);
	virtual Component* Clone() { return new LoginButtonScript(*this); };
};
