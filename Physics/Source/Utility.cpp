#include "Utility.h"
#include <string>
Position operator*(const Mtx44& lhs, const Position& rhs)
{
	float b[4];
	for (int i = 0; i < 4; i++)
		b[i] = lhs.a[0 * 4 + i] * rhs.x + lhs.a[1 * 4 + i] * rhs.y + lhs.a[2 * 4 + i] * rhs.z + lhs.a[3 * 4 + i] * 1;
	return Position(b[0], b[1], b[2]);
}
// converts string of format "x,y" into a vector3
Vector3 StringToVector(std::string s)
{
	std::string sX = s.substr(0, s.find(",", 0));
	std::string sY = s.substr(s.find(",", 0) + 1);

	return	Vector3((float)std::stoi(sX), (float)std::stoi(sY));
}
Locator::eLoggerUsers StringToUser(std::string s)
{
	if (s == "CHENG")
	{
		return Locator::CHENG;
	}
	else if (s == "KZ")
	{
		return Locator::KZ;
	}
	else if (s == "RYAN")
	{
		return Locator::RYAN;
	}
	else if (s == "LZ")
	{
		return Locator::LZ;
	}
	else if (s == "ALL")
	{
		return Locator::ALL;
	}
	else
	{
		DEFAULT_LOG("(Cheng) Unknown user: " + s + "Using ALL users as default");
		return Locator::ALL;
	}
}