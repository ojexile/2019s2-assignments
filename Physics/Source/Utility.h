#ifndef UTILITY_H
#define UTILITY_H

#include "Mtx44.h"
#include "Vertex.h"
#include "Locator.h"
#include "Vector3.h"

Position operator*(const Mtx44& lhs, const Position& rhs);
Vector3 StringToVector(std::string s);
// returns logger user enum
Locator::eLoggerUsers StringToUser(std::string s);
//Lerping
float Lerp(float start, float end, float rate);
Vector3 Lerp(Vector3 start, Vector3 end, float rate);
#endif