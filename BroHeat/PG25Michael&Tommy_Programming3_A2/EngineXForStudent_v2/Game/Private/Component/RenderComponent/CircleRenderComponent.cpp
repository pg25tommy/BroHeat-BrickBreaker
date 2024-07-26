#include "Game/Public/Component/RenderComponent/CircleRenderComponent.h"
#include "Engine/Public/EngineInterface.h"
#include "Game/Public/GameObject.h"

CircleRenderComponent::~CircleRenderComponent()
{
}

CircleRenderComponent::CircleRenderComponent(std::shared_ptr<GameObject> owner) :RenderComponent(owner)
{
	mRadius = 20.0f;
}

CircleRenderComponent::CircleRenderComponent(std::shared_ptr<GameObject> owner, float radius) :RenderComponent(owner)
{
	mRadius = radius;
}

CircleRenderComponent::CircleRenderComponent(std::shared_ptr<GameObject> owner, float radius, exColor color) :RenderComponent(owner,color)
{
	mRadius = radius;
}

CircleRenderComponent::CircleRenderComponent(std::shared_ptr<GameObject> owner, float radius, exColor color, int layer) : RenderComponent(owner, color,layer)
{
	mRadius = radius;
}

float CircleRenderComponent::GetRadius() const
{
	return mRadius;
}

void CircleRenderComponent::SetRadius(const float newRadius)
{
	mRadius = newRadius;
}

void CircleRenderComponent::Render(exEngineInterface* inEngineInterface)
{
	if (mOwner.expired()) {
		return;
	}
	std::shared_ptr<GameObject> owningGameObject = mOwner.lock();
	if (std::shared_ptr<TransformComponent> renderTransformComponent = owningGameObject->FindComponentOfType<TransformComponent>())
	{
		const exVector2 position = renderTransformComponent->GetPosition();
		inEngineInterface->DrawCircle(position, mRadius, mColor, 0);
	}
}
