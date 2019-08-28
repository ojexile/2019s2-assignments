#include "CoinUIScript.h"
#include "PlayerData.h"
#include "RenderComponent.h"

CoinUIScript::CoinUIScript()
{
}

CoinUIScript::~CoinUIScript()
{
}

void CoinUIScript::Update(double dt)
{
	RENDER->SetText(std::to_string(PlayerData::GetInstance()->GetCoins()) + " coins");
}