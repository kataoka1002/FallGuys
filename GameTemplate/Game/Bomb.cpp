#include "stdafx.h"
#include "Bomb.h"
#include "Player.h"
#include "BombInformation.h"
#include "Game.h"
#include "BrownBlock.h"

namespace
{
	//キャラコンの高さ
	const float CHARACON_HEIGHT = 0.0f;

	//キャラコンの半径
	const float CHARACON_RADIUS = 25.0f;

	//膨張スピード
	const float SELLING_SPEED = 0.01f;

	//爆弾の待機場所
	const Vector3 BOMB_WAITING_POS = { 0.0f,-150.0f,0.0f };

	//爆弾の起爆までの時間
	const float BOMB_FUSE_TIME = 3.0f;

	//爆発の距離の元
	const float BOMB_EXPLOSION_ORIGINAL = 60.0f;
}

Bomb::Bomb()
{
	
}

Bomb::~Bomb()
{

}

void Bomb::Update()
{
	//拡大縮小
	SwellingModel();

	//起爆までの時間の処理
	FuseTime();

	//キャラクターコントローラーを使用して座標を更新
	//m_charaCon.SetRigidBodyPosition(m_position);
	m_model.SetPosition(m_position);
	m_model.SetScale(m_scale);
	m_model.Update();
}

void Bomb::InitModel()
{
	//初期位置は待機場所
	m_position = BOMB_WAITING_POS;

	//タイマーのセット
	m_timer = BOMB_FUSE_TIME;

	//モデルの初期化
	m_model.Init("Assets/modelData/item/bomb.tkm");
	m_model.SetPosition(m_position);
	m_model.SetRotation(m_rotation);
	m_model.SetScale(m_scale);
	m_model.Update();

	//キャラクターコントローラーを初期化
	//m_charaCon.Init(
	//	CHARACON_RADIUS,	//半径
	//	CHARACON_HEIGHT,	//高さ
	//	m_position			//座標
	//);
}

void Bomb::SwellingModel()
{
	//sin波を使って滑らかに大きさを変化させる
	//角度を大きくしていく
	m_degree += 10.0f;

	//360度で-1～1を一周するので0度に戻す
	if (m_degree >= 360.0f)
	{
		m_degree = 0.0f;
	}

	//角度をラジアンに変換
	float rad = m_degree * 3.141592f / 180.0f;

	//sinの値を求める
	float sinValue = sin(rad);

	//最終的な膨張速度を求める
	float sellingSpeed = SELLING_SPEED * sinValue;
	m_scale += sellingSpeed;
}

void Bomb::FuseTime()
{
	//セットされていないなら返す
	if (m_isSetBomb == false)
	{
		return;
	}

	//時間計測
	m_timer -= g_gameTime->GetFrameDeltaTime();

	if (m_timer <= 0.0f)
	{
		//爆発
		Explosion();

		//設置している爆弾の数を減少させる
		m_bombInfo->DecreaseBombCount(m_bombNumber);

		//爆弾のリセット
		ResetBomb();
	}
}

void Bomb::ResetBomb()
{
	//待機場所に戻す
	m_position = BOMB_WAITING_POS;

	//タイマーのリセット
	m_timer = BOMB_FUSE_TIME;

	//セットされていない状態にする
	m_isSetBomb = false;
}

void Bomb::Explosion()
{
	//爆発がこれ以上広がるかどうか
	bool isExplosionSpreadingRight = true;
	bool isExplosionSpreadingLeft = true;
	bool isExplosionSpreadingUp = true;
	bool isExplosionSpreadingDown = true;

	//ブロックを壊したかどうか
	bool isPreventRight = false;
	bool isPreventLeft = false;
	bool isPreventUp = false;
	bool isPreventDown = false;

	//爆破座標を管理するリスト
	std::vector<Vector3> explosionPosList;

	//ステータス分の爆破距離を伸ばす
	for (int i = 0; i <= m_parentPlayer->GetExplosionPow(); i++)
	{
		//上下左右の爆風を設定
		Vector3 rightExplosionPos = { m_position.x + (BOMB_EXPLOSION_ORIGINAL * i), m_position.y, m_position.z };
		Vector3 leftExplosionPos = { m_position.x - (BOMB_EXPLOSION_ORIGINAL * i), m_position.y, m_position.z };
		Vector3 upExplosionPos = { m_position.x, m_position.y, m_position.z + (BOMB_EXPLOSION_ORIGINAL * i) };
		Vector3 downExplosionPos = { m_position.x, m_position.y, m_position.z - (BOMB_EXPLOSION_ORIGINAL * i) };

		//壁になるブロックにぶつかったかどうか
		for (auto wallPos : m_bombInfo->GetWallBlockPositionList())
		{
			//ぶつかったらこれ以上広がらないように変数を変更する
			if (wallPos.x == rightExplosionPos.x && wallPos.y == rightExplosionPos.y && wallPos.z == rightExplosionPos.z)
			{
				isExplosionSpreadingRight = false;
				isPreventRight = true;
			}
			if (wallPos.x == leftExplosionPos.x && wallPos.y == leftExplosionPos.y && wallPos.z == leftExplosionPos.z)
			{
				isExplosionSpreadingLeft = false;
				isPreventLeft = true;
			}
			if (wallPos.x == upExplosionPos.x && wallPos.y == upExplosionPos.y && wallPos.z == upExplosionPos.z)
			{
				isExplosionSpreadingUp = false;
				isPreventUp = true;
			}
			if (wallPos.x == downExplosionPos.x && wallPos.y == downExplosionPos.y && wallPos.z == downExplosionPos.z)
			{
				isExplosionSpreadingDown = false;
				isPreventDown = true;
			}
		}

		//ブロックが消えて出来た空洞があるかをチェック
		for (auto cavityPos : m_bombInfo->GetCavityPositionList())
		{
			//あったら爆発が広がるように変数を変更する
			if (cavityPos.x == rightExplosionPos.x && cavityPos.y == rightExplosionPos.y && cavityPos.z == rightExplosionPos.z && isPreventRight == false)
			{
				isExplosionSpreadingRight = true;
			}
			if (cavityPos.x == leftExplosionPos.x && cavityPos.y == leftExplosionPos.y && cavityPos.z == leftExplosionPos.z && isPreventLeft == false)
			{
				isExplosionSpreadingLeft = true;
			}
			if (cavityPos.x == upExplosionPos.x && cavityPos.y == upExplosionPos.y && cavityPos.z == upExplosionPos.z && isPreventUp == false)
			{
				isExplosionSpreadingUp = true;
			}
			if (cavityPos.x == downExplosionPos.x && cavityPos.y == downExplosionPos.y && cavityPos.z == downExplosionPos.z && isPreventDown == false)
			{
				isExplosionSpreadingDown = true;
			}
		}

		//壊せるブロックがあるかをチェックする
		for (auto brown : m_bombInfo->GetBrownBlockList())
		{
			CheckForBrownBlock(brown, rightExplosionPos);
			CheckForBrownBlock(brown, leftExplosionPos);
			CheckForBrownBlock(brown, upExplosionPos);
			CheckForBrownBlock(brown, downExplosionPos);
		}

		//爆風を発生させる場所をリストに追加
		if (i == 0)
		{
			explosionPosList.emplace_back(m_position);
		}
		else
		{
			//爆風を広げれるなら座標を追加
			if (isExplosionSpreadingRight == true)
			{
				explosionPosList.emplace_back(rightExplosionPos);
			}
			if (isExplosionSpreadingLeft == true)
			{
				explosionPosList.emplace_back(leftExplosionPos);
			}
			if (isExplosionSpreadingUp == true)
			{
				explosionPosList.emplace_back(upExplosionPos);
			}
			if (isExplosionSpreadingDown == true)
			{
				explosionPosList.emplace_back(downExplosionPos);
			}
		}
	}

	for (auto pos : explosionPosList)
	{
		//エフェクトの再生
		EffectEmitter* m_effect = NewGO<EffectEmitter>(0);
		m_effect->Init(enEffectName_BombExplosion);
		m_effect->SetPosition(pos);
		m_effect->Play();
	}

	//プレイヤー4人分チェック
	for (int j = 0; j < 4; j++)
	{
		//プレイヤーがいないなら終わる
		if (m_player[j] == nullptr)
		{
			break;
		}

		//爆風とプレイヤーの位置関係の処理
		for (auto exPos : explosionPosList)
		{
			//爆風からプレイヤーまでの距離を求める
			Vector3 toPlayer = m_player[j]->GetPosition() - exPos;
			float toPlayerDis = toPlayer.Length();

			//一定距離以内なら
			if (toPlayerDis <= 30.0f)
			{
				//プレイヤーは死亡する
				m_player[j]->DeadPlayer();
			}
		}
	}
}

void Bomb::CheckForBrownBlock(BrownBlock* brownBlock, Vector3& exPos)
{
	//壊せるブロックがあったら
	if (brownBlock->GetPosition().x == exPos.x && brownBlock->GetPosition().y == exPos.y && brownBlock->GetPosition().z == exPos.z)
	{
		//元々壁判定だった座標を空洞に変更
		for (auto wallPos : m_bombInfo->GetWallBlockPositionList())
		{
			if (wallPos.x == brownBlock->GetPosition().x && wallPos.y == brownBlock->GetPosition().y && wallPos.z == brownBlock->GetPosition().z)
			{
				//空洞リストに追加
				m_bombInfo->AddCavityPosition(wallPos);

				//爆弾設置可能リストに追加
				m_bombInfo->AddBombPoint(wallPos);

				//レベルアップアイテムの設置
				m_bombInfo->SetLevelUpItem(wallPos);
				
				//ブロックの削除
				DeleteGO(brownBlock);
			}
		}
	}
}