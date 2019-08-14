#pragma once
#include "ComponentBase.h"
class UIButtonComponent :
	public ComponentBase
{
public:
	UIButtonComponent();
	virtual ~UIButtonComponent();
	virtual ComponentBase* Clone() { return new UIButtonComponent(*this); };

	virtual void Update(double dt) override;
};

