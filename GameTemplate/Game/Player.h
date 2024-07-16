#pragma once
#include "Character.h"
#include "BombInformation.h"
class IPlayerState;

class Player : public Character
{
public:
	//�A�j���[�V�����N���b�v
	enum EnAnimationClip
	{
		enAnimClip_Idle,
		enAnimClip_Walk,
		enAnimClip_Num
	};

	Player();
	~Player();
	void Update();

	void InitModel() override;
	void Move()		 override;
	void Turn()		 override;
	void OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName) override;// �A�j���[�V�����C�x���g�p�̊֐�

	void PlantBomb();

	void SetPlayerNo(const int no)
	{
		m_playerNo = no;
	}

	const int GetPlayerNo()
	{
		return m_playerNo;
	}

	void SetPosition(const Vector3& pos)
	{
		m_position = pos;
	}

	void DeadPlayer()
	{
		m_isPlayerDead = true;
	}

	const float GetExplosionPow()
	{
		return m_bombExplosionPow;
	}

	/// <summary>
	/// �����X�s�[�h���グ��(�ő�2.0)
	/// </summary>
	void LevelUpWalkSpeed()
	{		
		m_walkSpeed += 0.2f;
		m_walkSpeed = min(m_walkSpeed, 2.0f);
	}

	/// <summary>
	/// �Η͂��グ��(�ő�5�}�X)
	/// </summary>
	void LevelUpExplosionPow()
	{
		m_bombExplosionPow++;
		m_bombExplosionPow = min(m_bombExplosionPow, 5);
	}

	/// <summary>
	/// �u���锚�e�̌��𑝂₷(�ő�5��)
	/// </summary>
	void LevelUpBombCount()
	{		
		m_bombInfo->LevelUpBombCount(m_playerNo);
	}

	/// <summary>
	/// �Đ�����A�j���[�V�����N���b�v��ݒ肷��B
	/// </summary>
	/// <param name="enAnimationClip">�A�j���[�V�����N���b�v</param>
	/// <param name="complementTime">��Ԏ���</param>
	void SetAnimation(const EnAnimationClip enAnimationClip, const float complementTime)
	{
		m_currentAnimationClip = enAnimationClip;
		m_complementTime = complementTime;
	}

	CharacterController& GetCharaCon()
	{
		return m_charaCon;
	}

private:
	IPlayerState*		m_playerState = nullptr;
	BombInformation*	m_bombInfo = nullptr;
	AnimationClip		animationClips[enAnimClip_Num];				// �A�j���[�V�����N���b�v
	EnAnimationClip		m_currentAnimationClip = enAnimClip_Idle;	// ���ݐݒ肳��Ă���A�j���[�V�����N���b�v
	float				m_complementTime = 0.0f;					// �A�j���[�V�����̕⊮����
	int 				m_bombExplosionPow = 0;						// ���j�З�
	float				m_walkSpeed = 0.0f;							// ��������
	int					m_playerNo = 0;								// �v���C���[�̃i���o�[
	bool				m_isPlayerDead = false;						// �v���C���[�����񂾂��ǂ���
};