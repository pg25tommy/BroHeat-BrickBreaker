#include "Game/Public/GameObject/Ball.h"


Ball::Ball() : GameObject()
{

}

Ball::Ball(exVector2 position)
{
	mPosition = position;
	mRadius = 10.0f;
	mColor = exColor{255,255,255,255};
	mMaxSpeed = 10.0f;
	mStart = false;
}

Ball::Ball(exVector2 position, float radius)
{
	mPosition = position;
	mRadius = radius;
	mColor = exColor{ 255,255,255,255 };
	mMaxSpeed = 10.0f;
	mStart = false;
}

Ball::Ball(exVector2 position, float radius, exColor color)
{
	mPosition = position;
	mRadius = radius;
	mColor = color;
	mMaxSpeed = 10.0f;
	mStart = false;
}

Ball::Ball(float maxSpeed, exVector2 position, float radius, exColor color)
{
	mPosition = position;
	mRadius = radius;
	mColor = color;
	mMaxSpeed = maxSpeed;
	mStart = false;
}

Ball::~Ball()
{
}

bool Ball::IsStart() const
{
	return mStart;
}

void Ball::StartMoving()
{
	mStart = true;
}

void Ball::Tick(float deltaTime)
{
	float ballSpeed = mCircleColliderComponent->GetVelocity().magnitude();
	if (ballSpeed >= 5.0f) {
		mCircleColliderComponent->SetVelocity(mCircleColliderComponent->GetVelocity().normalized() * (ballSpeed - deltaTime));
	}
	GameObject::Tick(deltaTime);
}

void Ball::BeginPlay()
{
	GameObject::BeginPlay();
	mTransform = AddComponentOfType<TransformComponent>(mPosition);
	mCircleRenderComponent = AddComponentOfType<CircleRenderComponent>(mRadius, mColor, 2);
	mCircleColliderComponent = AddComponentOfType<CircleColliderComponent>(mRadius,false);
	mCircleColliderComponent->SetMaxSpeed(mMaxSpeed);
}
