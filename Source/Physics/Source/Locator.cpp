#include "Locator.h"

Logger Locator::DefaultLogger("DEFAULT", 0x0F);
Logger Locator::ChengLogger("CHENG", 0x0B);
Logger Locator::RyanLogger("RYAN", 0x0C);
Logger Locator::KZLogger("KZ", 0x0C);
Logger Locator::LZLogger("LZ", 0x0C);

Locator::Locator()
{
}

Locator::~Locator()
{
}

Logger& Locator::GetLogger(eLoggerUsers user)
{
	switch (user)
	{
	case Locator::DEFAULT:
		return DefaultLogger;
		break;
	case Locator::CHENG:
		return ChengLogger;
		break;
	case Locator::RYAN:
		return RyanLogger;
		break;
	case Locator::KZ:
		return KZLogger;
		break;
	case Locator::LZ:
		return LZLogger;
		break;
	default:
		return DefaultLogger;
		break;
	};
}