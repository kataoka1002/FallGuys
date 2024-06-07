#pragma once
class WoodBlockRender;
class Game;

class WoodBlock : public IGameObject
{
public:
	WoodBlock();
	~WoodBlock();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

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
	ModelRender				m_modelRender;					// ���f�������_�[�B
	WoodBlockRender*		m_woodBlockRender = nullptr;	// �O���[�u���b�N�����_�[�B
	Game*					m_game = nullptr;
};