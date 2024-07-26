#include "Game/Public/Component/RenderComponent/BoxRenderComponent.h"
#include "Engine/Public/EngineInterface.h"
#include "Game/Public/GameObject.h"

BoxRenderComponent::~BoxRenderComponent()
{
}

BoxRenderComponent::BoxRenderComponent(std::shared_ptr<GameObject> owner) :RenderComponent(owner)
{
	mSize = exVector2{ 20.0f,20.0f };
}

BoxRenderComponent::BoxRenderComponent(std::shared_ptr<GameObject> owner, exVector2 size) : RenderComponent(owner)
{
	mSize = size;
}

BoxRenderComponent::BoxRenderComponent(std::shared_ptr<GameObject> owner, exVector2 size, exColor color) : RenderComponent(owner, color)
{
	mSize = size;
}

BoxRenderComponent::BoxRenderComponent(std::shared_ptr<GameObject> owner, exVector2 size, exColor color, int layer) : RenderComponent(owner, color, layer)
{
	mSize = size;
}

exVector2 BoxRenderComponent::GetSize() const
{
	return mSize;
}

void BoxRenderComponent::SetSize(const exVector2 size)
{
	mSize = size;
}

void BoxRenderComponent::Render(exEngineInterface* inEngineInterface)
{
	if (mOwner.expired()) {
		return;
	}
	std::shared_ptr<GameObject> owningGameObject = mOwner.lock();
	if (std::shared_ptr<TransformComponent> renderTransformComponent = owningGameObject->FindComponentOfType<TransformComponent>())
	{
		const exVector2 position = renderTransformComponent->GetPosition();
		inEngineInterface->DrawBox(position, mSize + position, mColor, 0);
	}
}
