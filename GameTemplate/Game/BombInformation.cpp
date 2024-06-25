#include "stdafx.h"
#include "BombInformation.h"
#include "Bomb.h"
#include "Stage.h"
#include "Player.h"

BombInformation::BombInformation()
{

}

BombInformation::~BombInformation()
{

}

bool BombInformation::Start()
{	
	m_stage = FindGO<Stage>("stage");
	
	//爆弾を置ける場所の取得
	m_bombPoint = m_stage->GetBombPoint();

	//爆弾を20個生成
	int bombNum = 0;
	for (int i = 0; i < 20; i++)
	{
		m_bomb = NewGO<Bomb>(0, "bomb");
		m_bomb->SetBombNumber(bombNum);

		if (bombNum >= 0 && bombNum < 5)
		{
			//リストに追加
			m_bombs1P.emplace_back(m_bomb);
		}
		else if (bombNum >= 5 && bombNum < 10)
		{
			//リストに追加
			m_bombs2P.emplace_back(m_bomb);
		}
		else if (bombNum >= 10 && bombNum < 15)
		{
			//リストに追加
			m_bombs3P.emplace_back(m_bomb);
		}
		else if (bombNum >= 15 && bombNum < 20)
		{
			//リストに追加
			m_bombs4P.emplace_back(m_bomb);
		}

		bombNum++;
	}

	return true;
}

void BombInformation::Update()
{
	
}

void BombInformation::PlantBomb(int num)
{
	//プレイヤーのポジションを取得
	Vector3 playerPos = m_player[num]->GetPosition();

	//一番近いポイントまでの距離
	float shortestDistance = 10000.0f;

	//爆弾を置くポジション
	Vector3 plantingPosition = { 0.0f,0.0f,0.0f };

	for (auto point : m_bombPoint)
	{
		//プレイヤーのポジションからポイントまでのベクトルを求める
		Vector3 vec = point - playerPos;

		//そのベクトルの長さを求める
		float toPoint = vec.Length();

		//保存しておいた最短距離よりも小さいなら
		if (toPoint < shortestDistance)
		{
			//最短距離を更新する
			shortestDistance = toPoint;

			//爆弾を置くポジションを更新する
			plantingPosition = point;
		}
	}

	if (num == 0)
	{
		//爆弾を設置する
		SetBombAtPosition(m_bombs1P, plantingPosition);
	}
	else if (num == 1)
	{
		//爆弾を設置する
		SetBombAtPosition(m_bombs2P, plantingPosition);
	}
	else if (num == 2)
	{
		//爆弾を設置する
		SetBombAtPosition(m_bombs3P, plantingPosition);
	}
	else if (num == 3)
	{
		//爆弾を設置する
		SetBombAtPosition(m_bombs4P, plantingPosition);
	}
}

void BombInformation::SetBombAtPosition(std::vector<Bomb*>& bombList, Vector3& pos)
{
	for (auto bomb : bombList)
	{
		//設置するポイントに爆弾がすでに置かれていないかを確認する
		if (pos.x == bomb->GetPosition().x &&
			pos.y == bomb->GetPosition().y &&
			pos.z == bomb->GetPosition().z)
		{
			break;
		}

		//セットされてない爆弾なら
		if (bomb->GetIsSetBomb() == false)
		{
			//爆弾のポジションを更新
			bomb->SetBombPosition(pos);

			//セット完了
			bomb->SetBomb();

			break;
		}
	}
}

void BombInformation::Render(RenderContext& rc)
{

}