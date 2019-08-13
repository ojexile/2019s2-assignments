#pragma once
#include "ScriptComponent.h"
/********************************************************************************/
/*!
\author Hao Cheng
\brief
Scrippt to handle reticle movement. The reticle is a child of camera GO. Camera GO has no rotation as it uses a dir vector.
/*!
/********************************************************************************/
class ReticleScript :
	public ScriptComponent
{
public:
	ReticleScript();
	virtual ~ReticleScript();

	virtual ComponentBase* Clone() { return new ReticleScript(*this); };
	virtual void Start() override;
	virtual void Update(double dt) override;
};
