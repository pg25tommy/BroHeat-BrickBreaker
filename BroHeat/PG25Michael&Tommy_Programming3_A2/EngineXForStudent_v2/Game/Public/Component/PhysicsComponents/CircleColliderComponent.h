#pragma once
#include "Game/Public/Component/PhysicsComponent.h"
class CircleColliderComponent : public PhysicsComponent
{
	friend class BoxColliderComponent;
public:

	CircleColliderComponent() = delete;
	CircleColliderComponent(std::shared_ptr<GameObject> owner);
	CircleColliderComponent(std::shared_ptr<GameObject> owner, bool isStatic);
	CircleColliderComponent(std::shared_ptr<GameObject> owner, float radius ,bool isStatic);
	virtual void CollisionReaction(std::shared_ptr<PhysicsComponent> otherComponent) override;
	virtual void StuckReaction(std::shared_ptr<PhysicsComponent> otherComponent) override;

protected:
	virtual void InitializeComponent() override;
	virtual bool IsColliding(std::shared_ptr<PhysicsComponent> otherComponent) override;

private:
	float mRadius;

};

