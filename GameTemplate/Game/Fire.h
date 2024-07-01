#pragma once

class Fire : public IGameObject
{
public:
	Fire();
	~Fire();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	void SetPosition(Vector3& pos)
	{
		m_position = pos;
	}

private:
	CollisionObject*	m_collisionObject = nullptr;	// コリジョン
	Vector3				m_position = Vector3::Zero;		// 座標
	float				m_mileage = 0.0f;				// 走行距離
};