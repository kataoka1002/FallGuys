#include "stdafx.h"
#include "LevelUpItemInformation.h"
#include "FirePowerUp.h"
#include "WalkSpeedUp.h"
#include "BombCountUp.h"
#include "Stage.h"

LevelUpItemInformation::LevelUpItemInformation()
{

}

LevelUpItemInformation::~LevelUpItemInformation()
{
	for (auto fire : m_firePowerUpList)
	{
		DeleteGO(fire);
	}
	m_firePowerUpList.clear();

	for (auto walk : m_walkSpeedUpList)
	{
		DeleteGO(walk);
	}
	m_walkSpeedUpList.clear();

	for (auto bombCount : m_bombCountUpList)
	{
		DeleteGO(bombCount);
	}
	m_bombCountUpList.clear();
}

bool LevelUpItemInformation::Start()
{
	//�����̎�̕ύX
	std::srand(std::time(0));

	//�X�e�[�W��������
	m_stage = FindGO<Stage>("stage");

	//�A�C�e����u����ꏊ�̎擾
	m_itemPointList = m_stage->GetBombPoint();

	//�Η�UP�A�C�e���̍쐬
	for (int i = 0; i < 10; i++)
	{
		FirePowerUp* fire = NewGO<FirePowerUp>(0, "firepowerup");
		m_firePowerUpList.emplace_back(fire);
	}

	//���s���xUP�A�C�e���̍쐬
	for (int i = 0; i < 10; i++)
	{
		WalkSpeedUp* walk = NewGO<WalkSpeedUp>(0, "walkspeedup");
		m_walkSpeedUpList.emplace_back(walk);
	}

	//�u�����UP�A�C�e���̍쐬
	for (int i = 0; i < 10; i++)
	{
		BombCountUp* bombCount = NewGO<BombCountUp>(0, "bombcountup");
		m_bombCountUpList.emplace_back(bombCount);
	}

	return true;
}

void LevelUpItemInformation::Update()
{
	
}

void LevelUpItemInformation::SetLevelUpItem(Vector3& pos)
{
	if (rand() % 3 == 0)
	{
		//�o�Ă���A�C�e���̓����_��
		int ran = rand() % 3;

		if (ran == 0)
		{
			for (auto fire : m_firePowerUpList)
			{
				//�܂��Z�b�g����ĂȂ��Ȃ�
				if (fire->GetIsSet() == false)
				{
					//���W��ݒ�
					fire->SetPosition(pos);

					//�Z�b�g�ς݂ɂ���
					fire->SetIsSet();
					break;
				}
			}
		}
		else if (ran == 1)
		{
			for (auto bombItem : m_bombCountUpList)
			{
				//�܂��Z�b�g����ĂȂ��Ȃ�
				if (bombItem->GetIsSet() == false)
				{
					//���W��ݒ�
					bombItem->SetPosition(pos);

					//�Z�b�g�ς݂ɂ���
					bombItem->SetIsSet();
					break;
				}
			}
		}
		else if (ran == 2)
		{
			for (auto walkSpeedItem : m_walkSpeedUpList)
			{
				//�܂��Z�b�g����ĂȂ��Ȃ�
				if (walkSpeedItem->GetIsSet() == false)
				{
					//���W��ݒ�
					walkSpeedItem->SetPosition(pos);

					//�Z�b�g�ς݂ɂ���
					walkSpeedItem->SetIsSet();
					break;
				}
			}
		}
	}
}

void LevelUpItemInformation::Render(RenderContext& rc)
{

}