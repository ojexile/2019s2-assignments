#include "Locator.h"

Logger Locator::DefaultLogger;
Logger Locator::ChengLogger;
Logger Locator::RyanLogger;
Logger Locator::KZLogger;
Logger Locator::LZLogger;

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