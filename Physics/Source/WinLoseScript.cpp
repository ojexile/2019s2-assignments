#include "WinLoseScript.h"
#include "WorldValues.h"

WinLoseScript::WinLoseScript()
{
	SetActive(false);
	m_bIsWin = false;
}

WinLoseScript::~WinLoseScript()
{
}

void WinLoseScript::SetWin(bool b)
{
	m_bIsWin = b;
}

void WinLoseScript::Start()
{
	WorldValues::TimeScale = 0.1f;
}

void WinLoseScript::Update(double dt)
{
}