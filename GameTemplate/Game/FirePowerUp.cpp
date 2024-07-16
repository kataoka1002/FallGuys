#include "stdafx.h"
#include "FirePowerUp.h"
#include "Player.h"
#include "Game.h"

FirePowerUp::FirePowerUp()
{

}

FirePowerUp::~FirePowerUp()
{
	DeleteGO(m_collisionObject);
}

void FirePowerUp::Update()
{
	//�A�C�e���ɓ����������ǂ����̏���
	CalcHitItem();

	//�R���W�����̈ʒu��ύX
	m_collisionObject->SetPosition(m_position);

	//���f���̏��̍X�V
	m_model.SetPosition(m_position);
	m_model.SetRotation(m_rotation);
	m_model.SetScale(m_scale);
	m_model.Update();
}

void FirePowerUp::InitModel()
{
	//���f���̏�����
	m_model.Init("Assets/modelData/item/lighter.tkm");
	m_model.SetPosition(m_position);
	m_model.SetRotation(m_rotation);
	m_model.SetScale(m_scale);
	m_model.Update();

	//�R���W�����I�u�W�F�N�g���쐬����B
	m_collisionObject = NewGO<CollisionObject>(0);

	//����̃R���W�������쐬����B
	m_collisionObject->CreateSphere(
		m_position,				//���W
		Quaternion::Identity,	//��]
		15.0f					//���a
	);

	//�R���W�����I�u�W�F�N�g�������ō폜����Ȃ��悤�ɂ���
	m_collisionObject->SetIsEnableAutoDelete(false);
}

void FirePowerUp::CalcHitItem()
{
	//�v���C���[�̃��X�g�̎擾
	for (auto player : m_game->GetPlayerList())
	{
		//�v���C���[���A�C�e���̃R���W�����ɂԂ�������
		if (m_collisionObject->IsHit(player->GetCharaCon()))
		{
			//���e�̉Η͂��グ��
			player->LevelUpExplosionPow();

			//�����Ȃ��ʒu�Ɉړ�������
			m_position = Vector3{ 0.0f,-200.0f,0.0f };

			//���ꂽ��Ԃɂ���
			m_isTaken = true;

			break;
		}
	}
}