#include "stdafx.h"
#include "ItemBase.h"
#include "Game.h"

bool ItemBase::Start()
{
	//ゲームクラスを見つける
	m_game = FindGO<Game>("game");

	//モデルの初期化
	InitModel();

	return true;
}

void ItemBase::Render(RenderContext& rc)
{
	m_model.Draw(rc);
}