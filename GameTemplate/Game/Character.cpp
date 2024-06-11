#include "stdafx.h"
#include "Character.h"

bool Character::Start()
{
	//モデルの初期化
	InitModel();

	return true;
}

void Character::Render(RenderContext& rc)
{
	m_model.Draw(rc);
}