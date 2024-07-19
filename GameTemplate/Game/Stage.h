#pragma once
class GrayBlock;
class GrayBlockRender;
class BrownBlock;
class BrownBlockRender;
class WoodBlock;
class WoodBlockRender;
class YellowBlock;
class YellowBlockRender;

class Stage : public IGameObject
{
public:
	Stage();
	~Stage();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	void SetBlock(Vector3& pos, int& stageData);

	void SetStaticObject(int& blockNum);
	
	const std::vector<Vector3>& GetBombPoint() const
	{
		return m_bombPoint;
	}

	const std::vector<Vector3>& GetWallBlockPositionList() const
	{
		return m_wallBlockPositionList;
	}

	const std::vector<Vector3>& GetBrownBlockPositionList() const
	{
		return m_brownBlockPositionList;
	}

	const std::vector<BrownBlock*> GetBrownBlockList() const
	{
		return m_brownBlocks;
	}

private:
	//グレーのブロック
	std::vector<GrayBlock*> m_grayBlocks;
	GrayBlockRender* m_grayBlockRender = nullptr;
	int m_maxGrayBlock = 0;

	//茶色のブロック
	std::vector<BrownBlock*> m_brownBlocks;
	BrownBlockRender* m_brownBlockRender = nullptr;
	int m_maxBrownBlock = 0;

	//木のブロック
	std::vector<WoodBlock*> m_woodBlocks;
	WoodBlockRender* m_woodBlockRender = nullptr;
	int m_maxWoodBlock = 0;

	//黄色のブロック
	std::vector<YellowBlock*> m_yellowBlocks;
	YellowBlockRender* m_yellowBlockRender = nullptr;
	int m_maxYellowBlock = 0;

	//ステージの配列(１階)
	int m_stageData[13][15] =
	{
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2 },
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2 },
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2 },
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2 },
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2 },
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2 },
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2 },
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2 },
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2 },
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2 },
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2 },
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2 },
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2 },
	};

	//ステージの配列(２階)
	int m_stageData2[13][15] =
	{
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2 },
		{2,4,4,1,1,1,1,1,1,1,1,1,4,4,2 },
		{2,4,3,1,3,1,3,1,3,1,3,1,3,4,2 },
		{2,1,1,1,1,1,1,1,1,1,1,1,1,1,2 },
		{2,1,3,1,3,1,3,1,3,1,3,1,3,1,2 },
		{2,1,1,1,1,1,1,1,1,1,1,1,1,1,2 },
		{2,1,3,1,3,1,3,1,3,1,3,1,3,1,2 },
		{2,1,1,1,1,1,1,1,1,1,1,1,1,1,2 },
		{2,1,3,1,3,1,3,1,3,1,3,1,3,1,2 },
		{2,1,1,1,1,1,1,1,1,1,1,1,1,1,2 },
		{2,4,3,1,3,1,3,1,3,1,3,1,3,4,2 },
		{2,4,4,1,1,1,1,1,1,1,1,1,4,4,2 },
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2 },
	};

	std::vector<Vector3> m_bombPoint;
	std::vector<Vector3> m_wallBlockPositionList;
	std::vector<Vector3> m_brownBlockPositionList;
};