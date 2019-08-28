#pragma once
#include "ObserverComponent.h"
class BossObserverCom :
	public ObserverComponent
{
public:
	BossObserverCom();
	virtual ~BossObserverCom();
	virtual Component* Clone() { return new BossObserverCom(*this); };
};
