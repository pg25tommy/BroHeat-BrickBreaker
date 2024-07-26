#pragma once
#include "Game/Public/GameObject.h"
class Brick : public GameObject
{
public:

	Brick();
	Brick(exVector2 position);
	Brick(exVector2 position, exVector2 size);
	Brick(exVector2 position, exVector2 size, exColor color);
	Brick(int health, exVector2 position, exVector2 size, exColor color);
	~Brick();
	
	int GetHealth() const;
	exVector2 GetPosition() const;

	virtual void BeginPlay() override;

	void Tick(float deltaTime);
	bool IsAlive() const;

private:

	exVector2 mPosition;
	exVector2 mSize;
	exColor mColor;
	int mHealth;


	std::shared_ptr<TransformComponent> mTransform;
	std::shared_ptr<BoxRenderComponent> mBoxRenderComponent;
	std::shared_ptr<BoxColliderComponent> mBoxColliderComponent;

};

