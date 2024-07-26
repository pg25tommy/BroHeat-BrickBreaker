#pragma once
#include "Game/Public/GameObject.h"
class Boundary : public GameObject
{
public:

	Boundary();
	Boundary(exVector2 position);
	Boundary(exVector2 position, exVector2 size);
	Boundary(exVector2 position, exVector2 size, exColor color);
	~Boundary();

	virtual void BeginPlay() override;

	void Tick(float deltaTime);

private:

	bool isTrigger;
	exVector2 mPosition;
	exVector2 mSize;
	exColor mColor;

	std::shared_ptr<TransformComponent> mTransform;
	std::shared_ptr<BoxRenderComponent> mBoxRenderComponent;
	std::shared_ptr<BoxColliderComponent> mBoxColliderComponent;

};



