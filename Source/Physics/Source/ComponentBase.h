#pragma once
#include "Vector3.h"
#include <vector>
#include <string>
#include "Locator.h"
#include "ComponentMacros.h"
class ComponentBase
{
private:
	bool m_bStarted;
	std::vector<ComponentBase*>* m_vec_RefList = nullptr;
	bool m_bActive;
public:
	ComponentBase();
	virtual ~ComponentBase();
	ComponentBase(ComponentBase& com);

	void Init(std::vector<ComponentBase*>* refList);
	virtual void Update(double dt);

	template <class t>
	t* GetComponent(bool bOptional = false)
	{
		for (unsigned i = 0; i < (*m_vec_RefList).size(); ++i)
		{
			t* out = dynamic_cast<t*>((*m_vec_RefList)[i]);
			if (out)
				return out;
		}
		std::string sTypeName = typeid(t).name();
		if (!bOptional)
			DEFAULT_LOG("Component of type " + sTypeName + " not found");
		return nullptr;
	};
	virtual ComponentBase* Clone() = 0;

	virtual void CheckStarted();
	virtual void Start();

	bool IsActive();
	void SetActive(bool b);
	bool IsStarted();
	void SetStarted(bool);

	// Function accessors
	void Notify(ComponentBase* com, std::string msg);
};
