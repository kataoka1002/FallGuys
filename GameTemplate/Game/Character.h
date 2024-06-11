#pragma once

class Character : public IGameObject
{
public:
	//�R���X�g���N�^
	Character(){}
	//�f�X�g���N�^
	virtual ~Character(){}

	bool Start();
	void Render(RenderContext& rc);

	virtual void InitModel() = 0;
	virtual void Move() = 0;
	virtual void Turn() = 0;

protected:
	ModelRender			m_model;						// ���f��
	Vector3				m_position = Vector3::Zero;		// ���W
	Vector3				m_scale = Vector3::One;			// �X�P�[��
	Vector3				m_moveSpeed = Vector3::Zero;	// �ړ����x
	Vector3             m_rotSpeed = Vector3::Zero;		// ��]���x
	Vector3				m_forward = Vector3::Zero;		// �O����
	CharacterController m_charaCon;						// �L�����N�^�[�R���g���[���[
	Quaternion			m_rotation;						// �N�H�[�^�j�I��
	float				LStick_x = 0.0f;				// L�X�e�B�b�N���͗�(��)
	float				LStick_y = 0.0f;				// L�X�e�B�b�N���͗�(�c)

};