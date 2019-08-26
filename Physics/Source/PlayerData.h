#pragma once
#include "Singleton.h"
#include "AbilityBase.h"
class PlayerData : public Singleton<PlayerData>
{
private:
	AbilityBase* m_SelectedAbility;
	bool m_bAbility0;
	bool m_bAbility1;
	int m_iCoins;
public:
	PlayerData();
	~PlayerData();

	void SetAbility(AbilityBase* a);
	AbilityBase* GetAbility();
	int GetCoins();
	void OffsetCoins(int i);
	bool GetGetAbilityActivated(int i);
};
