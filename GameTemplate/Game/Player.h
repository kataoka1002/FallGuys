#pragma once
#include "Character.h"
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

private:
	IPlayerState*		m_playerState = nullptr;
	AnimationClip		animationClips[enAnimClip_Num];				// アニメーションクリップ
	EnAnimationClip		m_currentAnimationClip = enAnimClip_Idle;	// 現在設定されているアニメーションクリップ
	float				m_complementTime = 0.0f;					// アニメーションの補完時間
};