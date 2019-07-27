#pragma once
#include "ScriptComponent.h"
#include "MeshController.h"
class GauntletScript :
	public ScriptComponent
{
public:
	enum eSTONES
	{
		NONE,
		SOUL,
		REALITY,
		SPACE,
		POWER,
		TIME,
		MIND,

		TOTAL,
	};
private:
	eSTONES m_eStone;
	MeshController<Mesh>* m_MC;
	bool m_bInUse;
	float m_fStartTime;
	float m_fDuration;
	GameObject* m_Ball;
	GameObject* m_Text;
	float m_fCharge;

	void StopUse();
public:
	GauntletScript(GameObject* ball, GameObject* Text);
	virtual ~GauntletScript();
	virtual ComponentBase* Clone() { return new GauntletScript(*this); }
	virtual void Start() override;
	virtual void Update(double dt) override;

	void RotateForward();
	void RotateBackward();

	void Use();

	friend class ChargeBarScript;
};
