#pragma once
#include "game/Public/GameObject.h"
class Player : public GameObject
{
public:

	Player();
	Player(exVector2 position);
	Player(exVector2 position, exVector2 size);
	Player(exVector2 position, exVector2 size, exColor color);
	Player(int health, exVector2 position, exVector2 size, exColor color);
	~Player();

	int GetHealth() const;
	exVector2 GetPosition() const;

	virtual void BeginPlay() override;

	void Tick(float deltaTime);

private:

	exVector2 mPosition;
	exVector2 mSize;
	exColor mColor;
	int mHealth;

	std::shared_ptr<TransformComponent> mTransform;
	std::shared_ptr<BoxRenderComponent> mBoxRenderComponent;
	std::shared_ptr<BoxColliderComponent> mBoxColliderComponent;

};

