#pragma once
class YellowBlockRender;
class Game;

class YellowBlock : public IGameObject
{
public:
	YellowBlock();
	~YellowBlock();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	void SetStaticObject(int num);

	void SetTRS(Vector3 pos, Quaternion rot, Vector3 scale)
	{
		m_position = pos;
		m_rotation = rot;
		m_scale = scale;
	}

	void SetInstanceNo(int num)
	{
		m_instanceNo = num;
	}

private:
	int						m_instanceNo = 0;				// �C���X�^���X�ԍ��B
	Vector3					m_position;						// ���W�B
	Vector3					m_scale;						// �傫���B
	Quaternion				m_rotation;						// ��]�B
	YellowBlockRender*		m_yellowBlockRender = nullptr;	// ���F�u���b�N�����_�[�B
	Game*					m_game = nullptr;
	PhysicsStaticObject		m_phyStaticObject;				// �ÓI�����I�u�W�F�N�g
};