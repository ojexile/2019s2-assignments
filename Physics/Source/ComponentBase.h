#pragma once
#include <vector>
#include "Print.h"
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
	t* GetComponent()
	{
		for (unsigned i = 0; i < (*m_vec_RefList)->size(); ++i)
		{
			t* out = dynamic_cast<t*>((*m_vec_RefList)[i]);
			if (out)
				return out;
		}
		std::string sTypeName = typeid(t).name();
		Print::PrintLn("No component of type " + sTypeName + " found.");
		return nullptr;
	};
};
