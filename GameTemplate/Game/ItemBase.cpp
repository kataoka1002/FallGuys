#include "stdafx.h"
#include "ItemBase.h"

bool ItemBase::Start()
{
	//���f���̏�����
	InitModel();

	return true;
}

void ItemBase::Render(RenderContext& rc)
{
	m_model.Draw(rc);
}