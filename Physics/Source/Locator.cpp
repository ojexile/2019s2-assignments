#include "Locator.h"

Logger Locator::DefaultLogger;
Logger Locator::ChengLogger;
Logger Locator::NotChengLogger;

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
	case Locator::NOT_CHENG:
		return NotChengLogger;
		break;
	default:
		return DefaultLogger;
		break;
	};
}