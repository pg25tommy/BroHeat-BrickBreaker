#include "Game/Public/GameObject/Brick.h"

Brick::Brick()
{
}

Brick::Brick(exVector2 position)
{
	mPosition = position;
	mSize = exVector2{20.0f,20.0f};
	mColor = exColor{ 255,255,255,255 };
	mHealth = 1;
}

Brick::Brick(exVector2 position, exVector2 size)
{
	mPosition = position;
	mSize = size;
	mColor = exColor{255,255,255,255};
	mHealth = 1;
}

Brick::Brick(exVector2 position, exVector2 size, exColor color)
{
	mPosition = position;
	mSize = size;
	mColor = color;
	mHealth = 1;
}

Brick::Brick(int health, exVector2 position, exVector2 size, exColor color)
{
	mPosition = position;
	mSize = size;
	mColor = color;
	mHealth = health;
}

Brick::~Brick()
{
}

int Brick::GetHealth() const
{
	return mHealth;
}

exVector2 Brick::GetPosition() const
{
	return mPosition;
}


void Brick::Tick(float deltaTime)
{
	auto physicsComp = FindComponentOfType<PhysicsComponent>();
	if (physicsComp->CollideLastFrame) {
		mHealth -= 1;
		auto renderer = FindComponentOfType<RenderComponent>();
		switch (mHealth)
		{
		case 3:
			renderer->SetColor(exColor{ 255,0,0,255 });
			break;
		case 2:
			renderer->SetColor(exColor{ 0,255,0,255 });
			break;
		case 1:
			renderer->SetColor(exColor{ 0,255,255,255 });
			break;
		default:
			break;
		} 
	}

	GameObject::Tick(deltaTime);
}

bool Brick::IsAlive() const
{
	return mHealth >= 1;
}

void Brick::BeginPlay()
{
	GameObject::BeginPlay();
	mTransform = AddComponentOfType<TransformComponent>(mPosition);
	mBoxRenderComponent = AddComponentOfType<BoxRenderComponent>(mSize,mColor,2);
	mBoxColliderComponent = AddComponentOfType<BoxColliderComponent>(mSize, false);
}