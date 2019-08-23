#ifndef UTILITY_H
#define UTILITY_H

#include "Mtx44.h"
#include "Vertex.h"
#include "Locator.h"
#include "Vector3.h"
#include <string>

Position operator*(const Mtx44& lhs, const Position& rhs);
Vector3 StringToVector(std::string s);
// returns logger user enum
Locator::eLoggerUsers StringToUser(std::string s);
//Lerping
float Lerp(float start, float end, float rate);
Vector3 Lerp(Vector3 start, Vector3 end, float rate);

bool IsClose(Vector3 a, Vector3 b, float buffer);
std::string vtos(Vector3& v);
float AngleBetween(const Vector3 &a, const Vector3 &b);
float LerpAngle(float target, float current, float rate);
#endif