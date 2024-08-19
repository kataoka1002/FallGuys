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
	//乱数の種の変更
	std::srand(std::time(0));

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
	
}

void LevelUpItemInformation::SetLevelUpItem(Vector3& pos)
{
	if (rand() % 3 == 0)
	{
		//出てくるアイテムはランダム
		int ran = rand() % 3;

		if (ran == 0)
		{
			for (auto fire : m_firePowerUpList)
			{
				//まだセットされてないなら
				if (fire->GetIsSet() == false)
				{
					//座標を設定
					fire->SetPosition(pos);

					//セット済みにする
					fire->SetIsSet();
					break;
				}
			}
		}
		else if (ran == 1)
		{
			for (auto bombItem : m_bombCountUpList)
			{
				//まだセットされてないなら
				if (bombItem->GetIsSet() == false)
				{
					//座標を設定
					bombItem->SetPosition(pos);

					//セット済みにする
					bombItem->SetIsSet();
					break;
				}
			}
		}
		else if (ran == 2)
		{
			for (auto walkSpeedItem : m_walkSpeedUpList)
			{
				//まだセットされてないなら
				if (walkSpeedItem->GetIsSet() == false)
				{
					//座標を設定
					walkSpeedItem->SetPosition(pos);

					//セット済みにする
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