#include "Game/Public/GameObject/Boundary.h"

Boundary::Boundary()
{
}

Boundary::Boundary(exVector2 position)
{
	mPosition = position;
	mSize = exVector2{ 20.0f,20.0f };
	mColor = exColor{ 255,255,255,0 };
}

Boundary::Boundary(exVector2 position, exVector2 size)
{
	mPosition = position;
	mSize = size;
	mColor = exColor{ 255,255,255,0 };
}

Boundary::Boundary(exVector2 position, exVector2 size, exColor color)
{
	mPosition = position;
	mSize = size;
	mColor = color;
}

Boundary::~Boundary()
{
}

void Boundary::Tick(float deltaTime)
{
	GameObject::Tick(deltaTime);
}

void Boundary::BeginPlay()
{
	GameObject::BeginPlay();
	mTransform = AddComponentOfType<TransformComponent>(mPosition);
	mBoxRenderComponent = AddComponentOfType<BoxRenderComponent>(mSize, mColor, 2);
	mBoxColliderComponent = AddComponentOfType<BoxColliderComponent>(mSize, false);
	mBoxColliderComponent->SetIsStatic(true);
}