#include "Game/Public/Component/TransformComponent.h"

TransformComponent::~TransformComponent()
{
}

TransformComponent::TransformComponent(std::shared_ptr<GameObject> owner, exVector2 position, exVector2 scale, exVector2 rotation) : Component(owner)
{
	mPosition = position;
	mRotation = rotation;
	mScale = scale;
}

TransformComponent::TransformComponent(std::shared_ptr<GameObject> owner, exVector2 position) : Component(owner)
{
	mPosition = position;
	mRotation = { 0.0f,0.0f };
	mScale = { 1.0f,1.0f };
}

TransformComponent::TransformComponent(std::shared_ptr<GameObject> owner, exVector2&& position) : Component(owner)
{
	mPosition = position;
	mRotation = { 0.0f,0.0f };
	mScale = { 1.0f,1.0f };
}

exVector2 TransformComponent::GetPosition() const
{
	return mPosition;
}

void TransformComponent::SetPosition(const exVector2& newPosition)
{
	mPosition = newPosition;
}

void TransformComponent::SetRotation(const exVector2& newRotation)
{
	mRotation = newRotation;
}

void TransformComponent::SetScale(const exVector2& newScale)
{
	mScale = newScale;
}

void TransformComponent::InitializeComponent()
{
}
