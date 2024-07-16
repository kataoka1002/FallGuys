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
	//ステージを見つける
	m_stage = FindGO<Stage>("stage");

	//アイテムを置ける場所の取得
	m_itemPointList = m_stage->GetBombPoint();

	//火力UPアイテムの作成
	for (int i = 0; i < 10; i++)
	{
		FirePowerUp* fire = NewGO<FirePowerUp>(0, "firepowerup");
		m_firePowerUpList.emplace_back(fire);
	}

	//歩行速度UPアイテムの作成
	for (int i = 0; i < 10; i++)
	{
		WalkSpeedUp* walk = NewGO<WalkSpeedUp>(0, "walkspeedup");
		m_walkSpeedUpList.emplace_back(walk);
	}

	//置ける個数UPアイテムの作成
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