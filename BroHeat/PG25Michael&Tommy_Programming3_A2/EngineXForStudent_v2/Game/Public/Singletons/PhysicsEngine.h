#pragma once
#include "Game/Public/Utils.h"
#define PHYSICS_ENGINE PhysicsEngine::GetInstance()

class PhysicsComponent;

class PhysicsEngine
{
public:

	~PhysicsEngine();
	static PhysicsEngine& GetInstance();

	void Physics();
	void AddPhysicsComponent(std::shared_ptr<PhysicsComponent> physicsComponentToAdd);

private:
	PhysicsEngine();

	void Move();
	void Collide();

	std::vector<std::weak_ptr<PhysicsComponent>> mPhysicsComponentList;
	static std::unique_ptr<PhysicsEngine> sInstance;
};
