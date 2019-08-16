#pragma once
#include "ComponentBase.h"
/**********************************************************8*********************/
/*!
\author Hao Cheng
\brief
base observer component. During engine update. GO with this component is sent to
Generic subject to be updated
/*!
/********************************************************************************/
class ObserverComponent :
	public ComponentBase
{
public:
	ObserverComponent();
	virtual ~ObserverComponent();
	virtual void Notify(ComponentBase* com, std::string msg) = 0;
};

