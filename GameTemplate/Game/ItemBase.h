#pragma once

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

	Vector3& GetPosition()
	{
		return m_position;
	}

protected:
	ModelRender			m_model;						// ���f��
	Vector3				m_position = Vector3::Zero;		// ���W
	//Vector3				m_scale = Vector3::One;			// �傫��
	float				m_scale = 1.0f;
	Quaternion			m_rotation;						// �N�H�[�^�j�I��
	CharacterController m_charaCon;						// �L�����N�^�[�R���g���[���[
};

