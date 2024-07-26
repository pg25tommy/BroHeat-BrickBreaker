#pragma once
#include "Utils.h"
#include "Component.h"
#include "Game/Public/Component/TransformComponent.h"
#include "Game/Public/Component/RenderComponent.h"
#include "Game/Public/Component/PhysicsComponent.h"
#include "Game/Public/Component.h"
#include "Game/Public/Component/RenderComponent/CircleRenderComponent.h"
#include "Game/Public/Component/PhysicsComponents/CircleColliderComponent.h"
#include "Game/Public/Component/RenderComponent/BoxRenderComponent.h"
#include "Game/Public/Component/PhysicsComponents/BoxColliderComponent.h"

class GameObject : public std::enable_shared_from_this<GameObject>
{
public:
	GameObject();
	~GameObject();

	virtual void BeginPlay();
	virtual void EndPlay();
	virtual void Tick(float deltaTime);

	template<class ComponentType, typename... Args>
	std::shared_ptr<ComponentType> AddComponentOfType(Args...arguments) 
	{
		std::shared_ptr<ComponentType> componentToAdd = std::make_shared<ComponentType>(
			shared_from_this(),
			arguments ...
		);
		
		if (std::shared_ptr<Component> castedComponent = std::dynamic_pointer_cast<Component>(componentToAdd))
		{
			castedComponent->InitializeComponent();
		}

		mComponents.push_back(componentToAdd);
				
		return componentToAdd;
	}

	template<class ComponentType>
	std::shared_ptr<ComponentType> FindComponentOfType() {
		for (std::shared_ptr<Component> componentIter : mComponents) {

			if (std::shared_ptr<ComponentType> castedComponent = std::dynamic_pointer_cast<ComponentType>(componentIter) ){
				return castedComponent;
			}
		}
		return nullptr;
	}

protected:
	ComponentList mComponents;
};

