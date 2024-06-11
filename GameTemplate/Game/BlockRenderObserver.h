#pragma once
class Stage;
class BrownBlockRender;
class GrayBlockRender;
class WoodBlockRender;
class YellowBlockRender;

class BlockRenderObserver : public IGameObject
{
public:
	BlockRenderObserver();
	~BlockRenderObserver();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

private:
	Stage* m_stage = nullptr;
	BrownBlockRender* m_brownRender = nullptr;
	GrayBlockRender* m_grayRender = nullptr;
	WoodBlockRender* m_woodRender = nullptr;
	YellowBlockRender* m_yellowRender = nullptr;
};

