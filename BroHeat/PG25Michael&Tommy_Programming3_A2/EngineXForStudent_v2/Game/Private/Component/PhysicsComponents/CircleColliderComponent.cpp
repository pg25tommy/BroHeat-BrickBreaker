#include "Game/Public/Component/PhysicsComponents/CircleColliderComponent.h"
#include "Game/Public/GameObject.h"

CircleColliderComponent::CircleColliderComponent(std::shared_ptr<GameObject> owner): PhysicsComponent(owner)
{
	mRadius = 1.0f;
}

CircleColliderComponent::CircleColliderComponent(std::shared_ptr<GameObject> owner, bool isStatic ) : PhysicsComponent(owner,isStatic)
{
	mRadius = 1.0f;
}

CircleColliderComponent::CircleColliderComponent(std::shared_ptr<GameObject> owner, float radius, bool isStatic) : PhysicsComponent(owner,isStatic)
{
	mRadius = radius;
}

void CircleColliderComponent::InitializeComponent()
{
	PhysicsComponent::InitializeComponent();
}

bool CircleColliderComponent::IsColliding(std::shared_ptr<PhysicsComponent> otherComponent)
{
	//circle to circle
	if (std::shared_ptr<CircleColliderComponent> otherCircleCollider = std::dynamic_pointer_cast<CircleColliderComponent>(otherComponent)) {
		if (mOwner.expired() || otherCircleCollider->mOwner.expired()) {
			return false;
		}
		if (otherCircleCollider.get() == this) {
			return false;
		}
		std::shared_ptr<TransformComponent> owningTransformComp = mOwner.lock()->FindComponentOfType<TransformComponent>();
		std::shared_ptr<TransformComponent> otherTransformComp = otherCircleCollider->mOwner.lock()->FindComponentOfType<TransformComponent>();

		if (owningTransformComp && otherTransformComp) {
			exVector2 vectorBetweenCenterPoints = owningTransformComp->GetPosition() - otherTransformComp->GetPosition();
			// sqrt((x^2) + (y^2))
			float distanceBetweenCircle = std::sqrt((vectorBetweenCenterPoints.x * vectorBetweenCenterPoints.x) + (vectorBetweenCenterPoints.y * vectorBetweenCenterPoints.y));
			if (distanceBetweenCircle <= (mRadius + otherCircleCollider->mRadius)) {
				return true;
			}
		}
	}

	
	// circle to box
    if (std::shared_ptr<BoxColliderComponent> otherBoxCollider = std::dynamic_pointer_cast<BoxColliderComponent>(otherComponent)) {
        if (mOwner.expired() || otherBoxCollider->mOwner.expired()) {
            return false;
        }
        // this will not be box collider so no check
        std::shared_ptr<TransformComponent> owningTransformComp = mOwner.lock()->FindComponentOfType<TransformComponent>();
        std::shared_ptr<TransformComponent> otherTransformComp = otherBoxCollider->mOwner.lock()->FindComponentOfType<TransformComponent>();

        if (owningTransformComp && otherTransformComp) {

            exVector2 boxPos = otherTransformComp->GetPosition();
            exVector2 selfPos = owningTransformComp->GetPosition();

            exVector2 size = otherBoxCollider->mSize;

            //check which edge is closest on both axis
            float closestX = selfPos.x;
            float closestY = selfPos.y;

            if (closestX < boxPos.x) {
                closestX = boxPos.x;
            }
            else if (closestX > boxPos.x + size.x) {
                closestX = boxPos.x + size.x;
            }
            if (closestY < boxPos.y) {
                closestY = boxPos.y;
            }
            else if (closestY > boxPos.y + size.y) {
                closestY = boxPos.y + size.y;
            }

            //check the collision on the closest edge
            float distX = selfPos.x - closestX;
            float distY = selfPos.y - closestY;
            float distance = sqrt((distX * distX) + (distY * distY));

            if (distance <= mRadius) {
                return true;
            }
        }
    }
	return false;
}

void CircleColliderComponent::CollisionReaction(std::shared_ptr<PhysicsComponent> otherComponent)
{
    //circle to circle
    if (std::shared_ptr<CircleColliderComponent> otherCircleCollider = std::dynamic_pointer_cast<CircleColliderComponent>(otherComponent)) {
        
        if (mOwner.expired() || otherCircleCollider->mOwner.expired()) {
            return;
        }
        std::shared_ptr<TransformComponent> owningTransformComp = mOwner.lock()->FindComponentOfType<TransformComponent>();
        std::shared_ptr<TransformComponent> otherTransformComp = otherCircleCollider->mOwner.lock()->FindComponentOfType<TransformComponent>();

        exVector2 normal = (otherTransformComp->GetPosition() - owningTransformComp->GetPosition()).normalized();
        //currentComponent->mVelocity = exVector2{ -currentComponent->mVelocity.x, -currentComponent->mVelocity.y };
        exVector2 reflectVector = mVelocity - normal * 2 * mVelocity.dot(normal);
        mVelocity = reflectVector;
    }
    //cicle to box
    else if (std::shared_ptr<BoxColliderComponent> otherBoxCollider = std::dynamic_pointer_cast<BoxColliderComponent>(otherComponent)) {
        
        if (mOwner.expired() || otherBoxCollider->mOwner.expired()) {
            return;
        }
        //check edge
        std::shared_ptr<TransformComponent> owningTransformComp = mOwner.lock()->FindComponentOfType<TransformComponent>();
        std::shared_ptr<TransformComponent> otherTransformComp = otherBoxCollider->mOwner.lock()->FindComponentOfType<TransformComponent>();


        exVector2 boxPos = otherTransformComp->GetPosition();
        exVector2 selfPos = owningTransformComp->GetPosition();

        exVector2 size = otherBoxCollider->mSize;

        exVector2 normal = exVector2{ 0.0f,0.0f };

        //check which edge is closest on both axis
        float closestX = selfPos.x;
        float closestY = selfPos.y;

        if (closestX < boxPos.x) {
            closestX = boxPos.x;
        }
        else if (closestX > boxPos.x + size.x) {
            closestX = boxPos.x + size.x;
        }
        if (closestY < boxPos.y) {
            closestY = boxPos.y;
        }
        else if (closestY > boxPos.y + size.y) {
            closestY = boxPos.y + size.y;
        }

        normal = (exVector2{ closestX,closestY} - selfPos).normalized();

        
        exVector2 reflectVector = mVelocity - normal * 2 * mVelocity.dot(normal);
        mVelocity = reflectVector;
    }
}

void CircleColliderComponent::StuckReaction(std::shared_ptr<PhysicsComponent> otherComponent)
{
    //circle to circle
    if (std::shared_ptr<CircleColliderComponent> otherCircleCollider = std::dynamic_pointer_cast<CircleColliderComponent>(otherComponent)) {

        if (mOwner.expired() || otherCircleCollider->mOwner.expired()) {
            return;
        }
        std::shared_ptr<TransformComponent> owningTransformComp = mOwner.lock()->FindComponentOfType<TransformComponent>();
        std::shared_ptr<TransformComponent> otherTransformComp = otherCircleCollider->mOwner.lock()->FindComponentOfType<TransformComponent>();

        exVector2 normal = (otherTransformComp->GetPosition() - owningTransformComp->GetPosition()).normalized();
        //currentComponent->mVelocity = exVector2{ -currentComponent->mVelocity.x, -currentComponent->mVelocity.y };
        exVector2 reflectVector = mVelocity - normal * 2 * mVelocity.dot(normal);
        
        

        //mVelocity = reflectVector;
    }
    //cicle to box
    else if (std::shared_ptr<BoxColliderComponent> otherBoxCollider = std::dynamic_pointer_cast<BoxColliderComponent>(otherComponent)) {

        if (mOwner.expired() || otherBoxCollider->mOwner.expired()) {
            return;
        }
        //check edge
        std::shared_ptr<TransformComponent> owningTransformComp = mOwner.lock()->FindComponentOfType<TransformComponent>();
        std::shared_ptr<TransformComponent> otherTransformComp = otherBoxCollider->mOwner.lock()->FindComponentOfType<TransformComponent>();


        exVector2 boxPos = otherTransformComp->GetPosition();
        exVector2 selfPos = owningTransformComp->GetPosition();

        exVector2 size = otherBoxCollider->mSize;

        exVector2 normal = exVector2{ 0.0f,0.0f };

        //check which edge is closest on both axis
        float closestX = selfPos.x;
        float closestY = selfPos.y;

        if (closestX < boxPos.x) {
            closestX = boxPos.x;
        }
        else if (closestX > boxPos.x + size.x) {
            closestX = boxPos.x + size.x;
        }
        if (closestY < boxPos.y) {
            closestY = boxPos.y;
        }
        else if (closestY > boxPos.y + size.y) {
            closestY = boxPos.y + size.y;
        }

        normal = (exVector2{ closestX,closestY } - selfPos).normalized();


        exVector2 reflectVector = mVelocity - normal * 2 * mVelocity.dot(normal);
        //mVelocity = reflectVector;
    }

}
