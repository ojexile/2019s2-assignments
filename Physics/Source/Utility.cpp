#include "Utility.h"
#include <string>
#include "Time.h"
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
float Lerp(float start, float end, float rate)
{
	return start + (1 - pow(rate, Time::GetInstance()->GetDeltaTimeF())) * (end - start);
}
Vector3 Lerp(Vector3 start, Vector3 end, float rate)
{
	Vector3 out;
	out.x = Lerp(start.x, end.x, rate);
	out.y = Lerp(start.y, end.y, rate);
	out.z = Lerp(start.z, end.z, rate);
	return out;
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
// Extra
bool IsClose(Vector3 a, Vector3 b, float buffer)
{
	if (fabs(a.x - b.x) < buffer)
	{
		if (fabs(a.y - b.y) < buffer)
		{
			if (fabs(a.z - b.z) < buffer)
			{
				return true;
			}
		}
	}
	return false;
}
std::string vtos(Vector3& v)
{
	std::string out;
	out += "{";
	out += std::to_string(v.x);
	out += ", ";
	out += std::to_string(v.y);
	out += ", ";
	out += std::to_string(v.z);
	out += " }";
	return out;
}
float AngleBetween(const Vector3 &a, const Vector3 &b)
{
	float num = a.Dot(b);
	float den = a.Length() * b.Length();
	float RAngle = acos(num / den);
	float DAngle = Math::RadianToDegree(RAngle);
	return DAngle;
}

float LerpAngle(float target, float current, float rate)
{
	float dtheta = target - current;
	if (dtheta > 180)
		current += 2 * 180;
	else if (dtheta < -180) current -= 2 * 180;
	current = Lerp(current, target, rate);
	return current;
}