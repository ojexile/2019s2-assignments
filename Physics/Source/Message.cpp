#include "Message.h"

Message::Message(ComponentBase* com, std::string s)
	: m_sMessage(s)
	, m_Com(com)
{
}

Message::~Message()
{
}