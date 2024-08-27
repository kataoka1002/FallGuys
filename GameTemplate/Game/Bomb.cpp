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
	//壁ブロックにぶつかったかどうか
	bool isHitWallBlockRight = false;
	bool isHitWallBlockLeft = false;
	bool isHitWallBlockUp = false;
	bool isHitWallBlockDown = false;

	//茶色ブロックを壊したかどうか
	bool isRightBlockBreak = false;
	bool isLeftBlockBreak = false;
	bool isUpBlockBreak = false;
	bool isDownBlockBreak = false;

	//茶色ブロックにぶつかったかどうか
	bool isHitBrownBlockRight = false;
	bool isHitBrownBlockLeft = false;
	bool isHitBrownBlockUp = false;
	bool isHitBrownBlockDown = false;

	//爆発の拡大を止めるかどうか
	bool isStopExplosionRight = false;
	bool isStopExplosionLeft = false;
	bool isStopExplosionUp = false;
	bool isStopExplosionDown = false;

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

		//空洞座標にぶつかったかどうか
		bool isHitCavityPosRight = false;
		bool isHitCavityPosLeft = false;
		bool isHitCavityPosUp = false;
		bool isHitCavityPosDown = false;

		//壁になるブロック(黄色ブロック、フレームのブロック)にぶつかったかどうか
		for (auto wallPos : m_bombInfo->GetWallBlockPositionList())
		{
			//ぶつかったらこれ以上広がらないように変数を変更する
			if (wallPos.x == rightExplosionPos.x && wallPos.y == rightExplosionPos.y && wallPos.z == rightExplosionPos.z)
			{
				isHitWallBlockRight = true;
			}
			if (wallPos.x == leftExplosionPos.x && wallPos.y == leftExplosionPos.y && wallPos.z == leftExplosionPos.z)
			{
				isHitWallBlockLeft = true;
			}
			if (wallPos.x == upExplosionPos.x && wallPos.y == upExplosionPos.y && wallPos.z == upExplosionPos.z)
			{
				isHitWallBlockUp = true;
			}
			if (wallPos.x == downExplosionPos.x && wallPos.y == downExplosionPos.y && wallPos.z == downExplosionPos.z)
			{
				isHitWallBlockDown = true;
			}
		}

		//ブロックが消えて出来た空洞があるかをチェック
		for (auto cavityPos : m_bombInfo->GetCavityPositionList())
		{
			//あったら爆発が広がるように変数を変更する
			if (cavityPos.x == rightExplosionPos.x && cavityPos.y == rightExplosionPos.y && cavityPos.z == rightExplosionPos.z)
			{
				isHitCavityPosRight = true;
			}
			if (cavityPos.x == leftExplosionPos.x && cavityPos.y == leftExplosionPos.y && cavityPos.z == leftExplosionPos.z)
			{
				isHitCavityPosLeft = true;
			}
			if (cavityPos.x == upExplosionPos.x && cavityPos.y == upExplosionPos.y && cavityPos.z == upExplosionPos.z)
			{
				isHitCavityPosUp = true;
			}
			if (cavityPos.x == downExplosionPos.x && cavityPos.y == downExplosionPos.y && cavityPos.z == downExplosionPos.z)
			{
				isHitCavityPosDown = true;
			}
		}

		if (i != 0)
		{
			//茶色ブロックにぶつかったかどうか
			for (auto brownPos : m_bombInfo->GetBrownBlockPositionList())
			{
				//ぶつかったらこれ以上広がらないように変数を変更する
				if (brownPos.x == rightExplosionPos.x && brownPos.y == rightExplosionPos.y && brownPos.z == rightExplosionPos.z)
				{
					isHitBrownBlockRight = true;
				}
				if (brownPos.x == leftExplosionPos.x && brownPos.y == leftExplosionPos.y && brownPos.z == leftExplosionPos.z)
				{
					isHitBrownBlockLeft = true;
				}
				if (brownPos.x == upExplosionPos.x && brownPos.y == upExplosionPos.y && brownPos.z == upExplosionPos.z)
				{
					isHitBrownBlockUp = true;
				}
				if (brownPos.x == downExplosionPos.x && brownPos.y == downExplosionPos.y && brownPos.z == downExplosionPos.z)
				{
					isHitBrownBlockDown = true;
				}
			}
		}

		//茶色ブロックがあるかをチェックする
		for (auto brown : m_bombInfo->GetBrownBlockList())
		{
			if (isRightBlockBreak == false && isHitWallBlockRight == false)
			{
				CheckForBrownBlock(brown, rightExplosionPos, isRightBlockBreak);
			}
			if (isLeftBlockBreak == false && isHitWallBlockLeft == false)
			{
				CheckForBrownBlock(brown, leftExplosionPos, isLeftBlockBreak);
			}
			if (isUpBlockBreak == false && isHitWallBlockUp == false)
			{
				CheckForBrownBlock(brown, upExplosionPos, isUpBlockBreak);
			}
			if (isDownBlockBreak == false && isHitWallBlockDown == false)
			{
				CheckForBrownBlock(brown, downExplosionPos, isDownBlockBreak);
			}
		}

		//爆風を発生させる場所をリストに追加
		if (i == 0)
		{
			explosionPosList.emplace_back(m_position);
		}
		else
		{
			//爆風を広げれるなら座標を追加
			if (((isHitWallBlockRight == false && isHitBrownBlockRight == false) || (isHitWallBlockRight == false && isHitCavityPosRight == true)) && isStopExplosionRight == false)
			{
				explosionPosList.emplace_back(rightExplosionPos);
			}
			//広げれないなら爆風を止めるフラグを立てる
			else if (isHitBrownBlockRight == true && isHitCavityPosRight == false)
			{
				isStopExplosionRight = true;
			}

			if (((isHitWallBlockLeft == false && isHitBrownBlockLeft == false) || (isHitWallBlockLeft == false && isHitCavityPosLeft == true)) && isStopExplosionLeft == false)
			{
				explosionPosList.emplace_back(leftExplosionPos);
			}
			else if (isHitBrownBlockLeft == true && isHitCavityPosLeft == false)
			{
				isStopExplosionLeft = true;
			}

			if (((isHitWallBlockUp == false && isHitBrownBlockUp == false) || (isHitWallBlockUp == false && isHitCavityPosUp == true)) && isStopExplosionUp == false)
			{
				explosionPosList.emplace_back(upExplosionPos);
			}
			else if (isHitBrownBlockUp == true && isHitCavityPosUp == false)
			{
				isStopExplosionUp = true;
			}

			if (((isHitWallBlockDown == false && isHitBrownBlockDown == false) || (isHitWallBlockDown == false && isHitCavityPosDown == true)) && isStopExplosionDown == false)
			{
				explosionPosList.emplace_back(downExplosionPos);
			}
			else if (isHitBrownBlockDown == true && isHitCavityPosDown == false)
			{
				isStopExplosionDown = true;
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

void Bomb::CheckForBrownBlock(BrownBlock* brownBlock, Vector3& exPos, bool& isBlockBreak)
{
	//茶色ブロックがあったら
	if (brownBlock->GetPosition().x == exPos.x && brownBlock->GetPosition().y == exPos.y && brownBlock->GetPosition().z == exPos.z)
	{
		//元々壁判定だった茶色ブロックの座標を空洞に変更
		for (auto brownBlockPos : m_bombInfo->GetBrownBlockPositionList())
		{
			if (brownBlockPos.x == brownBlock->GetPosition().x && brownBlockPos.y == brownBlock->GetPosition().y && brownBlockPos.z == brownBlock->GetPosition().z)
			{
				//空洞リストに追加
				m_bombInfo->AddCavityPosition(brownBlockPos);

				//爆弾設置可能リストに追加
				m_bombInfo->AddBombPoint(brownBlockPos);

				//レベルアップアイテムの設置
				m_bombInfo->SetLevelUpItem(brownBlockPos);
				
				//ブロックの削除
				DeleteGO(brownBlock);

				//ブロック削除済み
				isBlockBreak = true;

				//エフェクトの再生
				EffectEmitter* m_effect = NewGO<EffectEmitter>(0);
				m_effect->Init(enEffectName_BombExplosion);
				m_effect->SetPosition(brownBlockPos);
				m_effect->Play();
			}
		}
	}
}