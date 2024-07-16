#pragma once
class Game;

class ItemBase : public IGameObject
{
public:
	//�R���X�g���N�^
	ItemBase() {}
	//�f�X�g���N�^
	virtual ~ItemBase() {}

	bool Start();
	void Render(RenderContext& rc);

	virtual void InitModel() = 0;

	const Vector3& GetPosition() const
	{
		return m_position;
	}

	const void SetPosition(Vector3 pos)
	{
		m_position = pos;
	}

protected:
	Game*				m_game = nullptr;				// �Q�[��
	ModelRender			m_model;						// ���f��
	Vector3				m_position = {0.0f,-300.0f,0.0f};		// ���W
	//Vector3				m_scale = Vector3::One;			// �傫��
	float				m_scale = 1.0f;
	Quaternion			m_rotation;						// �N�H�[�^�j�I��
	//CharacterController m_charaCon;						// �L�����N�^�[�R���g���[���[
};