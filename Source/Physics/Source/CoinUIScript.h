#pragma once
#include "ScriptComponent.h"
class CoinUIScript :
	public ScriptComponent
{
public:
	CoinUIScript();
	virtual ~CoinUIScript();

	virtual Component* Clone() { return new CoinUIScript(*this); };

	virtual void Update(double dt) override;
};
