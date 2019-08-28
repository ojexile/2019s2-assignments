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
	GameObject* PassQ;
	GameObject* UserQ;
	GameObject* Selected;
	bool m_bTriggered;
public:
	LoginScript(GameObject* u, GameObject* p
		, GameObject* uq, GameObject* pq);
	virtual ~LoginScript();
	virtual Component* Clone() { return new LoginScript(*this); };
	virtual void Start() override;
	virtual void Update(double dt) override;
	void SetSelected(eSelectedSpace e);
	void LoginLocal();
	void CreateLocal();
};
