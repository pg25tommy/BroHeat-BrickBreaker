#include "game/public/GameObject/Player.h"

Player::Player()
{
}

Player::Player(exVector2 position)
{
	mPosition = position;
	mSize = exVector2{ 20.0f,20.0f };
	mColor = exColor{ 255,255,255,255 };
	mHealth = 1;
}

Player::Player(exVector2 position, exVector2 size)
{
	mPosition = position;
	mSize = size;
	mColor = exColor{ 255,255,255,255 };
	mHealth = 1;
}

Player::Player(exVector2 position, exVector2 size, exColor color)
{
	mPosition = position;
	mSize = size;
	mColor = color;
	mHealth = 1;
}

Player::Player(int health, exVector2 position, exVector2 size, exColor color)
{
	mPosition = position;
	mSize = size;
	mColor = color;
	mHealth = health;
}

Player::~Player()
{
}

int Player::GetHealth() const
{
	return mHealth;
}

exVector2 Player::GetPosition() const
{
	return mPosition;
}

void Player::BeginPlay()
{
	GameObject::BeginPlay();
	mTransform = AddComponentOfType<TransformComponent>(mPosition);
	mBoxRenderComponent = AddComponentOfType<BoxRenderComponent>(mSize, mColor, 2);
	mBoxColliderComponent = AddComponentOfType<BoxColliderComponent>(mSize, false);
}

void Player::Tick(float deltaTime)
{
	GameObject::Tick(deltaTime);
}
