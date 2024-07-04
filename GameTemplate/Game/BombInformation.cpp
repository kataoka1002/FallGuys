#include "stdafx.h"
#include "BombInformation.h"
#include "Bomb.h"
#include "Stage.h"
#include "Player.h"

namespace
{
	//置ける爆弾の最大数
	const int MAX_BOMB_COUNT = 1;
}

BombInformation::BombInformation()
{
	//置ける爆弾の最大数をセット
	m_maxBombCount1P = MAX_BOMB_COUNT;
	m_maxBombCount2P = MAX_BOMB_COUNT;
	m_maxBombCount3P = MAX_BOMB_COUNT;
	m_maxBombCount4P = MAX_BOMB_COUNT;
}

BombInformation::~BombInformation()
{

}

bool BombInformation::Start()
{	
	m_stage = FindGO<Stage>("stage");
	
	//爆弾を置ける場所の取得
	m_bombPoint = m_stage->GetBombPoint();

	//壁になるブロックの座標の取得
	m_wallBlockPositionList = m_stage->GetWallBlockPositionList();

	//爆弾を20個生成
	int bombNum = 0;
	for (int i = 0; i < 20; i++)
	{
		m_bomb = NewGO<Bomb>(0, "bomb");
		m_bomb->SetBombNumber(bombNum);
		m_bomb->SetPlayerPtr(m_player[0], m_player[1]);
		m_bomb->SetBombInfomation(this);

		if (bombNum >= 0 && bombNum < 5)
		{
			//親プレイヤーの設定
			m_bomb->SetParentPlayer(m_player[0]);

			//リストに追加
			m_bombs1P.emplace_back(m_bomb);
		}
		else if (bombNum >= 5 && bombNum < 10)
		{
			//親プレイヤーの設定
			m_bomb->SetParentPlayer(m_player[1]);

			//リストに追加
			m_bombs2P.emplace_back(m_bomb);
		}
		else if (bombNum >= 10 && bombNum < 15)
		{
			//親プレイヤーの設定
			m_bomb->SetParentPlayer(m_player[2]);

			//リストに追加
			m_bombs3P.emplace_back(m_bomb);
		}
		else if (bombNum >= 15 && bombNum < 20)
		{
			//親プレイヤーの設定
			m_bomb->SetParentPlayer(m_player[3]);

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

	//爆弾のリストを管理する配列
	std::vector<Bomb*> bombs[4] = { m_bombs1P ,m_bombs2P ,m_bombs3P ,m_bombs4P };

	//爆弾の設置
	SetBombAtPosition(bombs[num], plantingPosition, num);
}

void BombInformation::SetBombAtPosition(std::vector<Bomb*>& bombList, Vector3& pos, int& playerNum)
{
	// 各プレイヤーの設置した爆弾の数と最大設置数を格納する配列
	int m_plantBombCount[4] = { m_plantBombCount1P, m_plantBombCount2P, m_plantBombCount3P, m_plantBombCount4P };
	int m_maxBombCount[4] = { m_maxBombCount1P, m_maxBombCount2P, m_maxBombCount3P, m_maxBombCount4P };

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
			// 設置した爆弾の個数を増やす
			if (playerNum >= 0 && playerNum < 4 && m_plantBombCount[playerNum] < m_maxBombCount[playerNum])
			{
				// 爆弾のポジションを更新
				bomb->SetBombPosition(pos);

				// セット完了
				bomb->SetBomb();

				// 設置している爆弾の数を増やす
				m_plantBombCount[playerNum]++;
			}

			break;
		}
	}

	// 各プレイヤーの設置した爆弾の数を更新
	m_plantBombCount1P = m_plantBombCount[0];
	m_plantBombCount2P = m_plantBombCount[1];
	m_plantBombCount3P = m_plantBombCount[2];
	m_plantBombCount4P = m_plantBombCount[3];
}

void BombInformation::DecreaseBombCount(int& bombNum)
{
	// 各プレイヤーの爆弾カウントを配列で管理
	int* bombCounts[] = { &m_plantBombCount1P, &m_plantBombCount2P, &m_plantBombCount3P, &m_plantBombCount4P };

	// 対応するプレイヤーの爆弾カウントを減少させる
	if (bombNum >= 0 && bombNum < 20)
	{
		int index = bombNum / 5;
		(*bombCounts[index])--;
	}
}

void BombInformation::LevelUpBombCount(int& playerNum)
{
	//置ける爆弾の最大値の配列
	int* maxBombCount[4] = { &m_maxBombCount1P ,&m_maxBombCount2P ,&m_maxBombCount3P ,&m_maxBombCount4P };

	//置ける数を増やす(最大5個)
	(*maxBombCount[playerNum])++;
	(*maxBombCount[playerNum]) = min((*maxBombCount[playerNum]), 5);
}

void BombInformation::Render(RenderContext& rc)
{

}