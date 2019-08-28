#pragma once
#include "ScriptComponent.h"
class CheatScript :
	public ScriptComponent
{
private:
	GameObject* m_Sheet;
public:
	CheatScript(GameObject* Sheet);
	virtual ~CheatScript();
	virtual Component* Clone() { return new CheatScript(*this); };
	virtual void Update(double dt) override;
};
