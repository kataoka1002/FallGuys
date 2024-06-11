#pragma once

class Character : public IGameObject
{
public:
	//コンストラクタ
	Character(){}
	//デストラクタ
	virtual ~Character(){}

	bool Start();
	void Render(RenderContext& rc);

	virtual void InitModel() = 0;
	virtual void Move() = 0;
	virtual void Turn() = 0;

protected:
	ModelRender			m_model;						// モデル
	Vector3				m_position = Vector3::Zero;		// 座標
	Vector3				m_scale = Vector3::One;			// スケール
	Vector3				m_moveSpeed = Vector3::Zero;	// 移動速度
	Vector3             m_rotSpeed = Vector3::Zero;		// 回転速度
	Vector3				m_forward = Vector3::Zero;		// 前方向
	CharacterController m_charaCon;						// キャラクターコントローラー
	Quaternion			m_rotation;						// クォータニオン
	float				LStick_x = 0.0f;				// Lスティック入力量(横)
	float				LStick_y = 0.0f;				// Lスティック入力量(縦)

};