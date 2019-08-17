#pragma once
#include "ComponentBase.h"
#include <string>
class Message
{
	friend class GenericSubject;
private:
	std::string m_sMessage;
	Component* m_Com;
public:
	Message(Component* com, std::string s);
	~Message();
};
