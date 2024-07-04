#include "stdafx.h"
#include "WalkSpeedUp.h"

WalkSpeedUp::WalkSpeedUp()
{

}

WalkSpeedUp::~WalkSpeedUp()
{

}

void WalkSpeedUp::Update()
{

}

void WalkSpeedUp::InitModel()
{
	//ƒ‚ƒfƒ‹‚Ì‰Šú‰»
	m_model.Init("Assets/modelData/item/bomb.tkm");
	m_model.SetPosition(m_position);
	m_model.SetRotation(m_rotation);
	m_model.SetScale(m_scale);
	m_model.Update();
}