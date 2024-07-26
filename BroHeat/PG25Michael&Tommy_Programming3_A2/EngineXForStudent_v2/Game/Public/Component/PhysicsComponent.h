#pragma once
#include "Game/Public/Component.h"
#include "Engine/Public/EngineTypes.h"

typedef std::function<void(exVector2)> CollisionEventSignature;


class PhysicsComponent : public Component, public std::enable_shared_from_this<PhysicsComponent>
{
	friend class PhysicsEngine;
public:

	PhysicsComponent() = delete;
	~PhysicsComponent();

	PhysicsComponent(std::shared_ptr<GameObject> owner);
	PhysicsComponent(std::shared_ptr<GameObject> owner, bool isStatic);
	PhysicsComponent(std::shared_ptr<GameObject> owner, bool isStatic, bool isGravityEnabled);
	PhysicsComponent(std::shared_ptr<GameObject> owner, bool isStatic, bool isGravityEnabled, exVector2 velocity);


	void ListenToCollision(CollisionEventSignature eventToAdd);

	virtual bool IsColliding(std::shared_ptr<PhysicsComponent> otherComponent);
	virtual void CollisionReaction(std::shared_ptr<PhysicsComponent> otherComponent);
	virtual void StuckReaction(std::shared_ptr<PhysicsComponent> otherComponent);
	void AddForce(exVector2 velocity);

	// making the render function abstaract by putting = 0
	virtual void Physics();

	exVector2 GetVelocity();
	void SetVelocity(const exVector2 newVelocity);
	void SetIsStatic(bool isStatic);
	void SetMaxSpeed(float maxSpeed);
	bool CollideLastFrame;

protected:
	virtual void InitializeComponent() override;



protected:

	bool mIsStatic;
	bool mIsGravityEnabled;
	exVector2 mVelocity;
	float mMaxSpeed;

private:

	std::vector<CollisionEventSignature> mCollisionEvents;

};

