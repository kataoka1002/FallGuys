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
	CollisionObject*	m_collisionObject = nullptr;	// �R���W����
	Vector3				m_position = Vector3::Zero;		// ���W
	float				m_mileage = 0.0f;				// ���s����
};