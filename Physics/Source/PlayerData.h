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
		eHEAL,
		eSLOW_TIME,
	};
private:
	std::string m_sUser;
	std::string m_sPass;

	AbilityBase* m_SelectedAbility;
	int m_iCoins;
	bool m_bAbilityDash;
	bool m_bAbilityGrenade;
	eAbilities m_eAbiltiy;
public:
	PlayerData();
	~PlayerData();

	void SetAbility(AbilityBase* a, eAbilities e);
	AbilityBase* GetAbility();
	int GetCoins();
	void OffsetCoins(int i);
	bool GetAbilityActivated(eAbilities e);
	eAbilities GetCurrentAbility();
	void ActivateAbility(eAbilities e);

	void Save();
	bool Create(std::string user, std::string pass);
	bool Load(std::string user, std::string pass);

	std::string GetUsername();
};
