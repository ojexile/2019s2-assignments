#pragma once
#include "ScriptComponent.h"
#include "Vector3.h"
#include "GameObject.h"
class BlackholeScript :
	public ScriptComponent
{
private:
	float m_fMass;
	float m_fMinDist;
	std::vector<GameObject*> m_List;
public:
	BlackholeScript(float fMass, float fMinDist);
	virtual ~BlackholeScript();
	virtual Component* Clone()
	{
		return new BlackholeScript(*this);
	}

	void Update(double dt) override;
	void SetIgnoreList(std::vector<GameObject*> list);
};
