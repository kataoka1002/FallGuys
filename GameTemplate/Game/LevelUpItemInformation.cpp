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
	if (g_pad[0]->IsTrigger(enButtonLB1))
	{
		for (auto fire : m_firePowerUpList)
		{
			if (fire->GetIsTaken() == false)
			{
				fire->SetPosition(Vector3{ 0.0f,0.0f,0.0f });
				break;
			}
		}
		for (auto fire : m_bombCountUpList)
		{
			if (fire->GetIsTaken() == false)
			{
				fire->SetPosition(Vector3{ 120.0f,0.0f,0.0f });
				break;
			}
		}
		for (auto fire : m_walkSpeedUpList)
		{
			if (fire->GetIsTaken() == false)
			{
				fire->SetPosition(Vector3{ -120.0f,0.0f,0.0f });
				break;
			}
		}
	}
}

void LevelUpItemInformation::Render(RenderContext& rc)
{

}