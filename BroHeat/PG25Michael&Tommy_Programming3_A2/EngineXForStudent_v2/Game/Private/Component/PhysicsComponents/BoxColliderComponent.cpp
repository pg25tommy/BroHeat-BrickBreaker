#include "Game/Public/Component/PhysicsComponents/BoxColliderComponent.h"
#include "Game/Public/GameObject.h"

BoxColliderComponent::BoxColliderComponent(std::shared_ptr<GameObject> owner) : PhysicsComponent(owner)
{
    mSize = exVector2{ 20.0f,20.0f };;
}

BoxColliderComponent::BoxColliderComponent(std::shared_ptr<GameObject> owner, bool isStatic) : PhysicsComponent(owner, isStatic)
{
    mSize = exVector2{ 20.0f,20.0f };
}

BoxColliderComponent::BoxColliderComponent(std::shared_ptr<GameObject> owner, exVector2 size, bool isStatic) : PhysicsComponent(owner, isStatic)
{
    mSize = size;
}

void BoxColliderComponent::InitializeComponent()
{
    PhysicsComponent::InitializeComponent();
}

bool BoxColliderComponent::IsColliding(std::shared_ptr<PhysicsComponent> otherComponent)
{
    //Box to Box
	if (std::shared_ptr<BoxColliderComponent> otherBoxCollider = std::dynamic_pointer_cast<BoxColliderComponent>(otherComponent)) {
        if (mOwner.expired() || otherBoxCollider->mOwner.expired()) {
            return false;
        }        
        //check same component
        if (otherBoxCollider.get() == this) {
            return false;
        }

        std::shared_ptr<TransformComponent> owningTransformComp = mOwner.lock()->FindComponentOfType<TransformComponent>();
        std::shared_ptr<TransformComponent> otherTransformComp = otherBoxCollider->mOwner.lock()->FindComponentOfType<TransformComponent>();
		
        if (owningTransformComp && otherTransformComp) {
            exVector2 r1 = owningTransformComp->GetPosition();
            exVector2 r1s = mSize;
            exVector2 r2 = otherTransformComp->GetPosition();
            exVector2 r2s = otherBoxCollider->mSize;

            if (r1.x + r1s.x >= r2.x &&
                r1.x <= r2.x + r2s.x &&
                r1.y + r1s.y >= r2.y &&
                r1.y <= r2.y + r2s.y) {
                return true;
            }
        }
	}

    //Box to circle
    if (std::shared_ptr<CircleColliderComponent> otherCircleCollider = std::dynamic_pointer_cast<CircleColliderComponent>(otherComponent)) {
        if (mOwner.expired() || otherCircleCollider->mOwner.expired()) {
            return false;
        }
        // this will not be circle collider so no check
        std::shared_ptr<TransformComponent> owningTransformComp = mOwner.lock()->FindComponentOfType<TransformComponent>();
        std::shared_ptr<TransformComponent> otherTransformComp = otherCircleCollider->mOwner.lock()->FindComponentOfType<TransformComponent>();

        if (owningTransformComp && otherTransformComp) {

            exVector2 circlePos = otherTransformComp->GetPosition();
            exVector2 selfPos = owningTransformComp->GetPosition();

            //check which edge is closest on both axis
            float closestX = circlePos.x;
            float closestY = circlePos.y;

            if (closestX < selfPos.x) {
                closestX = selfPos.x;
            }
            else if (closestX > selfPos.x + mSize.x) {
                closestX = selfPos.x + mSize.x;
            }
            if (closestY < selfPos.y) {
                closestY = selfPos.y;
            }
            else if (closestY > selfPos.y + mSize.y) {
                closestY = selfPos.y + mSize.y;
            }

            //check the collision on the closest edge
            float distX = circlePos.x - closestX;
            float distY = circlePos.y - closestY;
            float distance = sqrt((distX * distX) + (distY * distY));

            if (distance <= otherCircleCollider->mRadius) {
                //CollideLastFrame = true;
                return true;
            }
        }
    }
    return false;
}

void BoxColliderComponent::CollisionReaction(std::shared_ptr<PhysicsComponent> otherComponent)
{
    if (std::shared_ptr<CircleColliderComponent> otherCircleCollider = std::dynamic_pointer_cast<CircleColliderComponent>(otherComponent)) {
        if (mOwner.expired() || otherCircleCollider->mOwner.expired()) {
            return;
        }
        otherCircleCollider->SetVelocity(mVelocity + otherCircleCollider->GetVelocity());
    }
}

void BoxColliderComponent::StuckReaction(std::shared_ptr<PhysicsComponent> otherComponent)
{
}

