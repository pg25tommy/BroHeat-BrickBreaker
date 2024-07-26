#include "Game/Public/Singletons/RenderEngine.h"
#include "Game/Public/Component/RenderComponent.h"
#include "Engine/Public/EngineInterface.h"

std::unique_ptr<RenderEngine> RenderEngine::sInstance = nullptr;

RenderEngine::RenderEngine()
{
}

RenderEngine::~RenderEngine()
{
}

RenderEngine& RenderEngine::GetInstance()
{
	if (!sInstance) {
		std::unique_ptr<RenderEngine> newInstance(new RenderEngine());

		sInstance = std::move(newInstance);
	}
	return *sInstance;
}

void RenderEngine::Render(exEngineInterface* renderEngine)
{
	for (std::weak_ptr<RenderComponent> componentToRender : mRenderComponents) {
		if (!componentToRender.expired()) {
			componentToRender.lock()->Render(renderEngine);
		}
	}
}

void RenderEngine::AddRenderingComponent(std::shared_ptr<RenderComponent> renderingComponentToAdd)
{
	mRenderComponents.push_back(renderingComponentToAdd);
}
