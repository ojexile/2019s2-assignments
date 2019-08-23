#pragma once
#include "ScriptComponent.h"
/********************************************************************************
Author: Ryan Tan Zheng Rong
Brief: An Augment that maybe be attached to a weaponPart that alters the
		Player/Gun/Bullet's stats/effects
********************************************************************************/

class Augment: public ScriptComponent
{
public:
	Augment();
	~Augment();

	enum eAugmentType
	{
		NIL,
		WEAPON,
		BULLET,
		PLAYER
	};

	virtual void ActiveEffect(Component* proj, GameObject* go) = 0;
	virtual void PassiveEffect() = 0;
	virtual void RemovePassive() = 0;

	void SetGunReference(ScriptComponent* ref);
	void SetEntityReference(ScriptComponent* ref);

	eAugmentType GetAugmentType();

protected:
	//Allows the augment to access the object's variables
	ScriptComponent* m_EntityRef;
	ScriptComponent* m_GunRef;

	eAugmentType m_AugmentType;
};

