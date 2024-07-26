#include "Game/Public/Component/RenderComponent.h"
#include "Game/Public/Singletons/RenderEngine.h"

RenderComponent::~RenderComponent()
{
}

RenderComponent::RenderComponent(std::shared_ptr<GameObject> owner) : Component(owner)
{
	mColor = {125,125,125,1};
	mLayer = 0;
}

RenderComponent::RenderComponent(std::shared_ptr<GameObject> owner, exColor color) : Component(owner)
{
	mColor = color;
	mLayer = 0;
}

RenderComponent::RenderComponent(std::shared_ptr<GameObject> owner, exColor color, int layer) : Component(owner)
{
	mColor = color;
	mLayer = layer;
}

exColor RenderComponent::GetColor() const
{
	return mColor;
}

void RenderComponent::SetColor(const exColor& newColor)
{
	mColor = newColor;
}

void RenderComponent::InitializeComponent()
{
	RegisterSelfToRenderEngine();
}

void RenderComponent::RegisterSelfToRenderEngine()
{
	RENDER_ENGINE.AddRenderingComponent(shared_from_this());
}
