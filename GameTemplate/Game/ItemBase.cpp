#include "stdafx.h"
#include "ItemBase.h"
#include "Game.h"

bool ItemBase::Start()
{
	//�Q�[���N���X��������
	m_game = FindGO<Game>("game");

	//���f���̏�����
	InitModel();

	return true;
}

void ItemBase::Render(RenderContext& rc)
{
	m_model.Draw(rc);
}