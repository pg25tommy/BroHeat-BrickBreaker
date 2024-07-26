#pragma once
#include "Game/Public/Component/RenderComponent.h"
#include "Game/Public/Component/TransformComponent.h"


class CircleRenderComponent :  public RenderComponent
{
public :
	CircleRenderComponent() = delete;
	~CircleRenderComponent();

	CircleRenderComponent(std::shared_ptr<GameObject> owner);
	CircleRenderComponent(std::shared_ptr<GameObject> owner,float radius);
	CircleRenderComponent(std::shared_ptr<GameObject> owner,float radius,exColor color);
	CircleRenderComponent(std::shared_ptr<GameObject> owner,float radius,exColor color, int layer);
	
	float GetRadius()const;
	void SetRadius(const float newRadius);

protected:

	virtual void Render(exEngineInterface* inEngineInterface);

private:
	float mRadius;
};

