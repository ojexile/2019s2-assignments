#pragma once
#include "ScriptComponent.h"

/*
author: lorenzo yanga
desc: one-time trigger script specialised for rotating the gameobject in real-time
*/

// TODO: create interactable script base class.
//		 don't think this will be the only interactable script class
class FlipEntityScript : public ScriptComponent
{
private:
	enum eFlipDirection
	{
		// TODO: see if these are the correct parameters to use
		FLIP_NORTH, // x positive
		FLIP_SOUTH, // x negative
		FLIP_EAST, // z positive
		FLIP_WEST // z negative
	};
	bool m_bIsTriggered;
	Vector3 m_vRotateDirectionInDegrees;
	float m_fTimeElapsed;

		
	FlipEntityScript();
	~FlipEntityScript();

	void Trigger(GameObject* go, GameObject* go2);

	/*
	when the interact triggers 
	pass the positions of player and interactable
	calculate the vector between the player and the interactable
	use vector (only need x and z value) to calculate trigger direction
	*/
	
};