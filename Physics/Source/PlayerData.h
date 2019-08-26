#pragma once
#include "Singleton.h"
#include "AbilityBase.h"
class PlayerData : public Singleton<PlayerData>
{
private:
	AbilityBase* m_SelectedAbility;
public:
	PlayerData();
	~PlayerData();

	void SetAbility(AbilityBase* a);
	AbilityBase* GetAbility();
};
