#pragma once

class Character : public IGameObject
{
public:
	//�R���X�g���N�^
	Character(){}
	//�f�X�g���N�^
	virtual ~Character(){}

	bool Start();

private:
	ModelRender m_model;				//���f��
};