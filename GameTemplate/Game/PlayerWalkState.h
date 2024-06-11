#pragma once
#include "IPlayerState.h"
class Player;

/// <summary>
/// �v���C���[�̕����X�e�[�g
/// </summary>
class PlayerWalkState : public IPlayerState
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="player">�v���C���[�̃C���X�^���X�B</param>
	PlayerWalkState(Player* player) : IPlayerState(player) {}

	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	~PlayerWalkState() override;

	/// <summary>
	/// �X�e�[�g�J�n���̏����B
	/// </summary>
	void Enter() override;

	/// <summary>
	/// �X�e�[�g�̑J�ڏ����B
	/// </summary>
	/// <returns>�J�ڂ���X�e�[�g</returns>
	IPlayerState* StateChange() override;

	/// <summary>
	/// �X�e�[�g�ɂ�����X�V�����B
	/// </summary>
	void Update() override;
};