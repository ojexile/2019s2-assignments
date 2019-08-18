#pragma once
class Stats
{
	friend class EntityScript;
private:
	//
	int m_iHealthMax;
	int m_iHealthRegenRate;
	float m_fStaminaMax;
	float m_fStaminaRegenRate;
	// movement
	float m_fMaxMovementSpeed;
	float m_fMovementForce;
public:
	Stats();
	~Stats();

	void SetZero();

	void SetHealth(int i);
	int GetHealth();
	void OffSetHealth(int i);
	void SetStamina(float f);
	float GetStamina();
	void OffsetStamina(float f);
	void SetStaminaRegen(float f);
	void SetMovement(float max, float force);
};
