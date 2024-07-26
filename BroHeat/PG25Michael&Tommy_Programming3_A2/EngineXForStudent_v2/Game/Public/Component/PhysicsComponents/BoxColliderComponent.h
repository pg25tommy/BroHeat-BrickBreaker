#pragma once
#include "Game/Public/Component/PhysicsComponent.h"
class BoxColliderComponent : public PhysicsComponent
{
	friend class CircleColliderComponent;
public:

	BoxColliderComponent() = delete;
	BoxColliderComponent(std::shared_ptr<GameObject> owner);
	BoxColliderComponent(std::shared_ptr<GameObject> owner, bool isStatic);
	BoxColliderComponent(std::shared_ptr<GameObject> owner, exVector2 size, bool isStatic);
	virtual void CollisionReaction(std::shared_ptr<PhysicsComponent> otherComponent) override;
	virtual void StuckReaction(std::shared_ptr<PhysicsComponent> otherComponent) override;

protected:
	virtual void InitializeComponent() override;
	virtual bool IsColliding(std::shared_ptr<PhysicsComponent> otherComponent) override;


private:
	exVector2 mSize;

};