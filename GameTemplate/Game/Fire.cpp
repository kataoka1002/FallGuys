#include "stdafx.h"
#include "Fire.h"

namespace
{
	//キャラコンの半径
	const float COLLISION_RADIUS = 25.0f;
}

Fire::Fire()
{

}

Fire::~Fire()
{
	//コリジョンの削除
	DeleteGO(m_collisionObject);
}

bool Fire::Start()
{
	//コリジョンオブジェクトを作成する
	m_collisionObject = NewGO<CollisionObject>(0);

	//球状のコリジョンを作成する
	m_collisionObject->CreateSphere(
		m_position,				//座標
		Quaternion::Identity,	//回転
		COLLISION_RADIUS		//半径
	);

	//コリジョンオブジェクトが自動で削除されないようにする
	m_collisionObject->SetIsEnableAutoDelete(false);

	return true;
}

void Fire::Update()
{
	m_position.x += 1.0f;
	m_mileage += 1.0f;

	//コリジョンの移動
	m_collisionObject->SetPosition(m_position);

	//if (m_collisionObject->IsHit())
	{

	}

	//一定距離移動したら
	if (m_mileage >= 60.0f)
	{
		DeleteGO(this);
	}
}

void Fire::Render(RenderContext& rc)
{

}