#include "stdafx.h"
#include "ItemBase.h"

bool ItemBase::Start()
{
	//ƒ‚ƒfƒ‹‚Ì‰Šú‰»
	InitModel();

	return true;
}

void ItemBase::Render(RenderContext& rc)
{
	m_model.Draw(rc);
}