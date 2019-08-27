#pragma once
#include "Singleton.h"
#include "AbilityBase.h"
class PlayerData : public Singleton<PlayerData>
{
public:
	enum eAbilities
	{
		eDASH,
		eGRENADE,
	};
private:
	AbilityBase* m_SelectedAbility;
	bool m_bAbilityDash;
	bool m_bAbilityGrenade;
	int m_iCoins;
public:
	PlayerData();
	~PlayerData();

	void SetAbility(AbilityBase* a);
	AbilityBase* GetAbility();
	int GetCoins();
	void OffsetCoins(int i);
	bool GetGetAbilityActivated(eAbilities e);
	void ActivateAbility(eAbilities e);
};
