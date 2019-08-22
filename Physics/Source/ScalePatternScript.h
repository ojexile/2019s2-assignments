#pragma once
#include "ScriptComponent.h"
/*
author: lorenzo yanga
desc: script to override the scale vector in the transform component with 
linear and non-linear patterns. mostly applicable with particles, but should be able to be used in any gameobjects too.
*/

class ScalePatternScript : public ScriptComponent
{
public:
	enum eScalePattern
	{
		SHRINK, // follows a -x graph, x = 0 when t seconds pass
		BREATHE // follows a sine graph up to 1 x pi (180 deg).
	};
private:
	eScalePattern m_scalePattern;
	float m_fMaximumScale;
	/*
	shrink -- max scale becomes highest point (start)
	breathe -- max scale becomes amplitude of the graph
	*/
	float m_fMaximumTimeElapsed; // lifetime
	float m_fTimeElapsed;
	float m_fScaleOffset;
	float m_fGradient;

public:
	//ScalePatternScript();
	ScalePatternScript(eScalePattern sp, float maxscale, float maxtime, float offset = 0.f);
	~ScalePatternScript();

	virtual void Update(double dt);
	virtual Component* Clone(){ return new ScalePatternScript(*this); }

};