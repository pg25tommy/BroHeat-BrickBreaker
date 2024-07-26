#pragma once
#include "Game/Public/GameObject.h"

class TransformComponent;
class CircleRenderComponet;

class Ball : public GameObject
{
public:

	Ball();
	Ball(exVector2 position);
	Ball(exVector2 position, float radius);
	Ball(exVector2 position, float radius, exColor color);
	Ball(float maxSpeed, exVector2 position, float radius, exColor color);
	~Ball();

	bool IsStart() const;
	void StartMoving();
	virtual void BeginPlay() override;
	void Tick(float deltaTime);

private:

	bool mStart;
	exVector2 mPosition;
	float mRadius;
	exColor mColor;
	float mMaxSpeed;

	std::shared_ptr<TransformComponent> mTransform;
	std::shared_ptr<CircleRenderComponent> mCircleRenderComponent;
	std::shared_ptr<CircleColliderComponent> mCircleColliderComponent;

};

