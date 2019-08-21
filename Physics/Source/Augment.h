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
	virtual void PassiveEffect(GameObject* go) = 0;

	void SetGunReference(GameObject* ref);
	void SetPlayerReference(ComponentBase* ref);

	eAugmentType GetAugmentType();

protected:
	ComponentBase* m_EntityRef;
	GameObject* m_GunRef;
	eAugmentType m_AugmentType;
};

