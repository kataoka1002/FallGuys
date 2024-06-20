#include "stdafx.h"
#include "Character.h"
#include "BombInformation.h"

bool Character::Start()
{
	m_bombInfo = FindGO<BombInformation>("bombinformation");

	//モデルの初期化
	InitModel();

	return true;
}

void Character::Render(RenderContext& rc)
{
	m_model.Draw(rc);
}