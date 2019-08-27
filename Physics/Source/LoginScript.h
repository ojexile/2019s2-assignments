#pragma once
#include "ScriptComponent.h"
class LoginScript :
	public ScriptComponent
{
public:
	enum eSelectedSpace
	{
		eUSER,
		ePASS,
	};
private:
	GameObject* User;
	GameObject* Pass;
	GameObject* Selected;
	bool m_bTriggered;
public:
	LoginScript(GameObject* u, GameObject* p);
	virtual ~LoginScript();
	virtual Component* Clone() { return new LoginScript(*this); };

	virtual void Update(double dt) override;
	void SetSelected(eSelectedSpace e);
	void LoginLocal();
	bool CreateLocal();
};
