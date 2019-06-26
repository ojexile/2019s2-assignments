#pragma once
#include <vector>
#include "Locator.h"
class ComponentBase
{
private:
	std::vector<ComponentBase*>* m_vec_RefList;
public:
	ComponentBase();
	virtual ~ComponentBase();

	void Init(std::vector<ComponentBase*>* refList);
	virtual void Update(double dt) = 0;

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
};
