#include "stdafx.h"
#include "ItemBase.h"

bool ItemBase::Start()
{
	//モデルの初期化
	InitModel();

	return true;
}

void ItemBase::Render(RenderContext& rc)
{
	m_model.Draw(rc);
}