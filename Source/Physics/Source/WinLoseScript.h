#pragma once
#include "ScriptComponent.h"
class WinLoseScript :
	public ScriptComponent
{
private:
	bool m_bIsWin;
public:
	WinLoseScript();
	virtual ~WinLoseScript();
	virtual Component* Clone() { return new WinLoseScript(*this); };
	void SetWin(bool b);

	virtual void Start() override;
	virtual void Update(double dt) override;
};
