#ifndef UTILITY_H
#define UTILITY_H

#include "Mtx44.h"
#include "Vertex.h"
#include "Locator.h"

Position operator*(const Mtx44& lhs, const Position& rhs);
Vector3 StringToVector(std::string s);
// returns logger user enum
Locator::eLoggerUsers StringToUser(std::string s);
#endif