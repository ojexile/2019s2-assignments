#pragma once
#include "Resources.h"
#include "Singleton.h"

/// used to hold string resouces
/// ContentPath MUST be first val in file
/// file path MUST be at root with name resouces.dat
class ResourceHandler : public Singleton<ResourceHandler>
{
private:
	Resources* m_Res;
	void InitResources();
protected:
	~ResourceHandler();
public:
	ResourceHandler();

	Resources* GetResources();
};
