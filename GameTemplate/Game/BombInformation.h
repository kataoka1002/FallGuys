#pragma once
class Bomb;
class Stage;
class Player;
class BrownBlock;
class LevelUpItemInformation;

class BombInformation : public IGameObject
{
public: 
	BombInformation();
	~BombInformation();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	/// <summary>
	/// ���x���A�b�v�A�C�e���̐ݒu������
	/// </summary>
	/// <param name="pos"></param>
	void SetLevelUpItem(Vector3& pos);

	/// <summary>
	/// ���e��ݒu����ꏊ�����߂�
	/// </summary>
	/// <param name="num">�v���C���[�̃i���o�[</param>
	void PlantBomb(int num);

	/// <summary>
	/// ���e��ݒu����
	/// </summary>
	/// <param name="bombList">���e�̃��X�g</param>
	/// <param name="pos">�ݒu�ꏊ</param>
	void SetBombAtPosition(std::vector<Bomb*>& bombList, Vector3& pos, int& playerNum);

	/// <summary>
	/// �v���C���[�̃|�C���^��ݒ肷��
	/// </summary>
	/// <param name="player0"></param>
	/// <param name="player1"></param>
	/// <param name="player2"></param>
	/// <param name="player3"></param>
	void SetPlayerPtr(Player* player0 = nullptr, Player* player1 = nullptr, Player* player2 = nullptr, Player* player3 = nullptr)
	{
		m_player[0] = player0;
		m_player[1] = player1;
		m_player[2] = player2;
		m_player[3] = player3;
	}

	const std::vector<Vector3>& GetWallBlockPositionList() const
	{
		return m_wallBlockPositionList;
	}

	const std::vector<Vector3>& GetCavityPositionList() const
	{
		return m_cavityPositionList;
	}

	const std::vector<BrownBlock*> GetBrownBlockList() const
	{
		return m_brownBlocks;
	}

	const std::vector<Vector3>& GetBrownBlockPositionList() const
	{
		return m_brownBlockPositionList;
	}

	/// <summary>
	/// �ݒu���Ă��锚�e�̐�������������
	/// </summary>
	/// <param name="bombNum"></param>
	void DecreaseBombCount(int& bombNum);

	/// <summary>
	/// �u���锚�e�̌��𑝂₷(�ő�5��)
	/// </summary>
	void LevelUpBombCount(int& playerNum);

	/// <summary>
	/// �󓴂̍��W��ǉ�����
	/// </summary>
	/// <param name="pos"></param>
	/// <returns></returns>
	const void AddCavityPosition(Vector3& pos)
	{
		m_cavityPositionList.emplace_back(pos);
	}

	/// <summary>
	/// ���e��u������W��ǉ�����
	/// </summary>
	/// <param name="pos"></param>
	/// <returns></returns>
	const void AddBombPoint(Vector3& pos)
	{
		m_bombPoint.emplace_back(pos);
	}

private:
	Bomb* m_bomb = nullptr;
	Stage* m_stage = nullptr;
	Player* m_player[4] = { nullptr,nullptr,nullptr,nullptr };
	LevelUpItemInformation* m_levelUpItemInfo = nullptr;
	std::vector<Bomb*> m_bombs1P;
	std::vector<Bomb*> m_bombs2P;
	std::vector<Bomb*> m_bombs3P;
	std::vector<Bomb*> m_bombs4P;
	std::vector<Vector3> m_bombPoint;
	std::vector<Vector3> m_wallBlockPositionList;
	std::vector<Vector3> m_brownBlockPositionList;
	std::vector<Vector3> m_bombPlantedPosition;
	std::vector<Vector3> m_cavityPositionList;
	std::vector<BrownBlock*> m_brownBlocks;
	int m_maxBombCount1P = 0;
	int m_maxBombCount2P = 0;
	int m_maxBombCount3P = 0;
	int m_maxBombCount4P = 0;
	int m_plantBombCount1P = 0;
	int m_plantBombCount2P = 0;
	int m_plantBombCount3P = 0;
	int m_plantBombCount4P = 0;
};