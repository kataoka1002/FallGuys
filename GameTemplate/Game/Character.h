#pragma once

class Character : public IGameObject
{
public:
	//コンストラクタ
	Character(){}
	//デストラクタ
	virtual ~Character(){}

	bool Start();

private:
	ModelRender m_model;				//モデル
};