#pragma once
#include "ScriptComponent.h"
class PaddleScript :
	public ScriptComponent
{
private:
	bool m_bIsLeft;
public:
	PaddleScript(bool b);
	virtual ~PaddleScript();
	virtual ComponentBase* Clone()
	{
		return new PaddleScript(*this);
	}
	virtual void Update(double dt) override;
};
