#pragma once
#include "ScriptComponent.h"
#include "ChunkData.h"
/********************************************************************************/
/*!
\author Hao Cheng
\brief
Script to handle reticle movement. The reticle is a child of camera GO. Camera GO has no rotation as it uses a dir vector.
/*!
/********************************************************************************/
class ReticleScript :
	public ScriptComponent
{
private:
	Vector3 m_vOffset;
public:
	ReticleScript();
	virtual ~ReticleScript();

	virtual Component* Clone() { return new ReticleScript(*this); };
	virtual void Start() override;
	virtual void Update(double dt) override;
};
