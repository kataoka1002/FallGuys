#include "stdafx.h"
#include "FirePowerUp.h"

FirePowerUp::FirePowerUp()
{

}

FirePowerUp::~FirePowerUp()
{

}

void FirePowerUp::Update()
{

}

void FirePowerUp::InitModel()
{
	//���f���̏�����
	m_model.Init("Assets/modelData/item/bomb.tkm");
	m_model.SetPosition(m_position);
	m_model.SetRotation(m_rotation);
	m_model.SetScale(m_scale);
	m_model.Update();
}