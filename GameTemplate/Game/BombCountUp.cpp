#include "stdafx.h"
#include "BombCountUp.h"

BombCountUp::BombCountUp()
{

}

BombCountUp::~BombCountUp()
{

}

void BombCountUp::Update()
{

}

void BombCountUp::InitModel()
{
	//���f���̏�����
	m_model.Init("Assets/modelData/item/bomb.tkm");
	m_model.SetPosition(m_position);
	m_model.SetRotation(m_rotation);
	m_model.SetScale(m_scale);
	m_model.Update();
}