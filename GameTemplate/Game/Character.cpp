#include "stdafx.h"
#include "Character.h"

bool Character::Start()
{
	//���f���̏�����
	InitModel();

	return true;
}

void Character::Render(RenderContext& rc)
{
	m_model.Draw(rc);
}