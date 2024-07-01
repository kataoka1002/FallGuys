#include "stdafx.h"
#include "Fire.h"

namespace
{
	//�L�����R���̔��a
	const float COLLISION_RADIUS = 25.0f;
}

Fire::Fire()
{

}

Fire::~Fire()
{
	//�R���W�����̍폜
	DeleteGO(m_collisionObject);
}

bool Fire::Start()
{
	//�R���W�����I�u�W�F�N�g���쐬����
	m_collisionObject = NewGO<CollisionObject>(0);

	//����̃R���W�������쐬����
	m_collisionObject->CreateSphere(
		m_position,				//���W
		Quaternion::Identity,	//��]
		COLLISION_RADIUS		//���a
	);

	//�R���W�����I�u�W�F�N�g�������ō폜����Ȃ��悤�ɂ���
	m_collisionObject->SetIsEnableAutoDelete(false);

	return true;
}

void Fire::Update()
{
	m_position.x += 1.0f;
	m_mileage += 1.0f;

	//�R���W�����̈ړ�
	m_collisionObject->SetPosition(m_position);

	//if (m_collisionObject->IsHit())
	{

	}

	//��苗���ړ�������
	if (m_mileage >= 60.0f)
	{
		DeleteGO(this);
	}
}

void Fire::Render(RenderContext& rc)
{

}