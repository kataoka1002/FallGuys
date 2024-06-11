#pragma once
#include "IPlayerState.h"
class Player;

/// <summary>
/// プレイヤーの待機ステート
/// </summary>
class PlayerIdleState : public IPlayerState
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="player">プレイヤーのインスタンス。</param>
	PlayerIdleState(Player* player) : IPlayerState(player) {}

	/// <summary>
	/// デストラクタ。
	/// </summary>
	~PlayerIdleState() override;

	/// <summary>
	/// ステート開始時の処理。
	/// </summary>
	void Enter() override;

	/// <summary>
	/// ステートの遷移処理。
	/// </summary>
	/// <returns>遷移するステート</returns>
	IPlayerState* StateChange() override;

	/// <summary>
	/// ステートにおける更新処理。
	/// </summary>
	void Update() override;
};