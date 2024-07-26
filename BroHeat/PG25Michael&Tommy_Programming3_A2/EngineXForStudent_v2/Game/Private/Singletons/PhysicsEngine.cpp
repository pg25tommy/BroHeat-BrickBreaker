#include "Game/Public/Singletons/PhysicsEngine.h"
#include "Game/Public/GameObject.h"
//#include "Game/Public/Component/PhysicsComponent.h"

std::unique_ptr<PhysicsEngine> PhysicsEngine::sInstance = nullptr;


PhysicsEngine::PhysicsEngine()
{
}
PhysicsEngine::~PhysicsEngine()
{
}

void PhysicsEngine::AddPhysicsComponent(std::shared_ptr<PhysicsComponent> physicsComponentToAdd)
{
    mPhysicsComponentList.push_back(physicsComponentToAdd);
}

void PhysicsEngine::Move()
{
    for (std::weak_ptr<PhysicsComponent> physicsComponentIter : mPhysicsComponentList) {
        if (physicsComponentIter.expired()) {
            continue;
        }
        std::shared_ptr<PhysicsComponent> currentComponent = physicsComponentIter.lock();
        if (!currentComponent) {
            continue;
        }
        currentComponent->Physics();

    }
}

void PhysicsEngine::Collide()
{
    for (std::weak_ptr<PhysicsComponent> physicsComponentIter : mPhysicsComponentList)
    {
        if (physicsComponentIter.expired())
        {
            continue;
        }
        std::shared_ptr<PhysicsComponent> currentComponent = physicsComponentIter.lock();
        bool collide = false;
        for (std::weak_ptr<PhysicsComponent> otherPhysicsComponentIter : mPhysicsComponentList)
        {
         /*   if (physicsComponentIter.expired())
            {
                continue;
            }*/

            if (otherPhysicsComponentIter.expired())
            {
                continue;
            }

            //std::shared_ptr<PhysicsComponent> currentComponent = physicsComponentIter.lock();
            std::shared_ptr<PhysicsComponent> otherComponent = otherPhysicsComponentIter.lock();
            if (!currentComponent || !otherComponent)
            {
                continue;
            }
            if (currentComponent->IsColliding(otherComponent)) {
                if (currentComponent->CollideLastFrame) {
                    //stuck
                    //circle to circle
                    if (std::shared_ptr<CircleColliderComponent> currentCircleCollider = std::dynamic_pointer_cast<CircleColliderComponent>(currentComponent)) {
                        currentCircleCollider->StuckReaction(otherComponent);
                    }
                    //cicle to box
                    else if (std::shared_ptr<BoxColliderComponent> currentBoxCollider = std::dynamic_pointer_cast<BoxColliderComponent>(currentComponent)) {
                        //this guy do nothing cuz box are statics in my game
                        currentBoxCollider->StuckReaction(otherComponent);
                    }
                    //currentComponent->mVelocity = exVector2{ -currentComponent->mVelocity.x, -currentComponent->mVelocity.y };

                }
                else {
                    //not stuck
                    //circle to circle
                    if (std::shared_ptr<CircleColliderComponent> currentCircleCollider = std::dynamic_pointer_cast<CircleColliderComponent>(currentComponent)) {
                        currentCircleCollider->CollisionReaction(otherComponent);
                    }
                    //cicle to box
                    else if (std::shared_ptr<BoxColliderComponent> currentBoxCollider = std::dynamic_pointer_cast<BoxColliderComponent>(currentComponent)) {
                        //this guy do nothing cuz box are statics in my game
                        currentBoxCollider->CollisionReaction(otherComponent);
                    }
                    //currentComponent->mVelocity = exVector2{ -currentComponent->mVelocity.x, -currentComponent->mVelocity.y };

                }


                collide = true;
            }
        }
        //std::shared_ptr<PhysicsComponent> currentComponent = physicsComponentIter.lock();
        currentComponent->CollideLastFrame = collide;
    }
}


PhysicsEngine& PhysicsEngine::GetInstance()
{
    if (!sInstance) {
        std::unique_ptr<PhysicsEngine> newInstance(new PhysicsEngine());

        sInstance = std::move(newInstance);
    }
    return *sInstance;
}

void PhysicsEngine::Physics()
{
    Collide();
    Move();
}



