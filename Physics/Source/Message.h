#pragma once
#include "ComponentBase.h"
#include <string>
class Message
{
	friend class GenericSubject;
private:
	std::string m_sMessage;
	ComponentBase* m_Com;
public:
	Message(ComponentBase* com, std::string s);
	~Message();
};
