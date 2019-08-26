#pragma once
class EntityValues
{
	friend class EntityScript;
private:
	int m_iHealth;
	float m_fStamina;
public:
	EntityValues();
	~EntityValues();

	float GetStamina();
	void OffsetStamina(float f);
	int GetHealth();
	void SetHealth(int i);
	void HealHealth(int i);
};
