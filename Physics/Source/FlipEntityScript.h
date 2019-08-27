#pragma once
#include "InteractionBaseScript.h"

/*
author: lorenzo yanga
desc: one-time trigger script specialised for rotating the gameobject in real-time
*/

// TODO: create interactable script base class.
//		 don't think this will be the only interactable script class
class FlipEntityScript : public InteractionBaseScript
{
private:
	enum eFlipDirection
	{
		// TODO: see if these are the correct parameters to use
		FLIP_NONE,
		FLIP_NORTH, // x positive
		FLIP_SOUTH, // x negative
		FLIP_EAST, // z positive
		FLIP_WEST // z negative
	};
	float m_fRotationAmount;
	eFlipDirection m_flipDirection;
	//Vector3 m_vflipDirection;
public:

	FlipEntityScript();
	virtual ~FlipEntityScript();

	virtual void Update(double dt) override;
	virtual void Trigger(ComponentBase* player) override;

	virtual Component* Clone() { return new FlipEntityScript(*this); };
	/*
	when the interact triggers 
	pass the positions of player and interactable
	calculate the vector between the player and the interactable
	use vector (only need x and z value) to calculate trigger direction
	*/
	
};