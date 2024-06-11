#pragma once
#include "Player.h"
class Player;

/// <summary>
/// �v���C���[�X�e�[�g���N���X/// </summary>
class IPlayerState
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="player">�v���C���[</param>
	IPlayerState(Player* player) : m_player(player) {}

	/// <summary>
	/// �f�X�X�g���N�^
	/// </summary>
	virtual ~IPlayerState() {}

	/// <summary>
	/// �X�e�[�g�J�n���̏����B
	/// </summary>
	virtual void Enter() = 0;

	/// <summary>
	/// �X�e�[�g�̑J�ڏ����B
	/// </summary>
	/// <returns>�J�ڂ���X�e�[�g</returns>
	virtual IPlayerState* StateChange() = 0;

	/// <summary>
	/// �e�X�e�[�g�ɂ�����X�V�����B
	/// </summary>
	virtual void Update() = 0;

protected:
	Player* m_player = nullptr;		// �v���C���[
};