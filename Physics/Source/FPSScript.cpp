#include "FPSScript.h"
FPSScript::FPSScript()
{
}

FPSScript::~FPSScript()
{
}
void FPSScript::Start()
{
	rc = RENDER;
}
void FPSScript::Update(double dt)
{
	rc = RENDER;
	rc->SetText(std::to_string(1 / dt));
}