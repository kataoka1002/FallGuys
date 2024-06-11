#include "stdafx.h"
#include "Character.h"

bool Character::Start()
{
	//ƒ‚ƒfƒ‹‚Ì‰Šú‰»
	InitModel();

	return true;
}

void Character::Render(RenderContext& rc)
{
	m_model.Draw(rc);
}