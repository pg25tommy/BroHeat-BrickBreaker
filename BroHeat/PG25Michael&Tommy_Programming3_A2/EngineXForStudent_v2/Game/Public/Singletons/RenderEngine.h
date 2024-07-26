#pragma once
#include "Game/Public/Utils.h"
#define RENDER_ENGINE RenderEngine::GetInstance()

class exEngineInterface;
class RenderComponent;

class RenderEngine
{
public:
	~RenderEngine();
	static RenderEngine& GetInstance();

	void Render(exEngineInterface* renderEngine);
	void AddRenderingComponent(std::shared_ptr<RenderComponent> renderingComponentToAdd);


private:
	RenderEngine();

	std::vector<std::weak_ptr<RenderComponent>> mRenderComponents;
	static std::unique_ptr<RenderEngine> sInstance;
};

