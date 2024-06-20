#include "stdafx.h"
#include "Character.h"
#include "BombInformation.h"

bool Character::Start()
{
	m_bombInfo = FindGO<BombInformation>("bombinformation");

	//ƒ‚ƒfƒ‹‚Ì‰Šú‰»
	InitModel();

	return true;
}

void Character::Render(RenderContext& rc)
{
	m_model.Draw(rc);
}