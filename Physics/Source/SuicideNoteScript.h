#pragma once
#include "ScriptComponent.h"
#include "StopWatch.h"
class SuicideNoteScript :
	public ScriptComponent
{
	const float m_fLifeTime;
	StopWatch s;
public:
	SuicideNoteScript(float fLifeTime);
	virtual ~SuicideNoteScript();
	virtual Component* Clone() { return new SuicideNoteScript(*this); };
	virtual void Start() override;

	virtual void Update(double dt) override;
};
