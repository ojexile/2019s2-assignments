#pragma once
class Stats
{
	friend class EntityScript;
private:
	//
	int m_iHealth;
	int m_iHealthMax;
	float m_fStaminaMax;
	float m_fStaminaRegenRate;
	// movement
	float m_fMaxMovementSpeed;
	float m_fMovementForce;
public:
	Stats();
	~Stats();

	void SetHealth(int i);
	int GetHealth();
	void SetStamina(float f);
	float GetStamina();
	void SetStaminaRegen(float f);
	void SetMovement(float max, float force);
};
