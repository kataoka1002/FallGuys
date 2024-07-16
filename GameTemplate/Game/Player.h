#pragma once
#include "Character.h"
#include "BombInformation.h"
class IPlayerState;

class Player : public Character
{
public:
	//アニメーションクリップ
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
	void OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName) override;// アニメーションイベント用の関数

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
	/// 歩くスピードを上げる(最大2.0)
	/// </summary>
	void LevelUpWalkSpeed()
	{		
		m_walkSpeed += 0.2f;
		m_walkSpeed = min(m_walkSpeed, 2.0f);
	}

	/// <summary>
	/// 火力を上げる(最大5マス)
	/// </summary>
	void LevelUpExplosionPow()
	{
		m_bombExplosionPow++;
		m_bombExplosionPow = min(m_bombExplosionPow, 5);
	}

	/// <summary>
	/// 置ける爆弾の個数を増やす(最大5個)
	/// </summary>
	void LevelUpBombCount()
	{		
		m_bombInfo->LevelUpBombCount(m_playerNo);
	}

	/// <summary>
	/// 再生するアニメーションクリップを設定する。
	/// </summary>
	/// <param name="enAnimationClip">アニメーションクリップ</param>
	/// <param name="complementTime">補間時間</param>
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
	AnimationClip		animationClips[enAnimClip_Num];				// アニメーションクリップ
	EnAnimationClip		m_currentAnimationClip = enAnimClip_Idle;	// 現在設定されているアニメーションクリップ
	float				m_complementTime = 0.0f;					// アニメーションの補完時間
	int 				m_bombExplosionPow = 0;						// 爆破威力
	float				m_walkSpeed = 0.0f;							// 歩く速さ
	int					m_playerNo = 0;								// プレイヤーのナンバー
	bool				m_isPlayerDead = false;						// プレイヤーが死んだかどうか
};