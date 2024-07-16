#include "stdafx.h"
#include "WalkSpeedUp.h"
#include "Player.h"
#include "Game.h"

WalkSpeedUp::WalkSpeedUp()
{

}

WalkSpeedUp::~WalkSpeedUp()
{

}

void WalkSpeedUp::Update()
{
	//アイテムに当たったかどうかの処理
	CalcHitItem();

	//コリジョンの位置を変更
	m_collisionObject->SetPosition(m_position);

	//モデルの情報の更新
	m_model.SetPosition(m_position);
	m_model.SetRotation(m_rotation);
	m_model.SetScale(m_scale);
	m_model.Update();
}

void WalkSpeedUp::InitModel()
{
	//モデルの初期化
	m_model.Init("Assets/modelData/item/shoe.tkm");
	m_model.SetPosition(m_position);
	m_model.SetRotation(m_rotation);
	m_model.SetScale(m_scale);
	m_model.Update();

	//コリジョンオブジェクトを作成する。
	m_collisionObject = NewGO<CollisionObject>(0);

	//球状のコリジョンを作成する。
	m_collisionObject->CreateSphere(
		m_position,				//座標
		Quaternion::Identity,	//回転
		25.0f					//半径
	);

	//コリジョンオブジェクトが自動で削除されないようにする
	m_collisionObject->SetIsEnableAutoDelete(false);
}

void WalkSpeedUp::CalcHitItem()
{
	//プレイヤーのリストの取得
	for (auto player : m_game->GetPlayerList())
	{
		//プレイヤーがアイテムのコリジョンにぶつかったら
		if (m_collisionObject->IsHit(player->GetCharaCon()))
		{
			//歩くスピードを上げる
			player->LevelUpWalkSpeed();

			//見えない位置に移動させる
			m_position = Vector3{ 0.0f,-200.0f,0.0f };

			//取られた状態にする
			m_isTaken = true;

			break;
		}
	}
}