#pragma once

class ItemBase : public IGameObject
{
public:
	//コンストラクタ
	ItemBase() {}
	//デストラクタ
	virtual ~ItemBase() {}

	bool Start();
	void Render(RenderContext& rc);

	virtual void InitModel() = 0;

	Vector3& GetPosition()
	{
		return m_position;
	}

protected:
	ModelRender			m_model;						// モデル
	Vector3				m_position = Vector3::Zero;		// 座標
	//Vector3				m_scale = Vector3::One;			// 大きさ
	float				m_scale = 1.0f;
	Quaternion			m_rotation;						// クォータニオン
	CharacterController m_charaCon;						// キャラクターコントローラー
};

