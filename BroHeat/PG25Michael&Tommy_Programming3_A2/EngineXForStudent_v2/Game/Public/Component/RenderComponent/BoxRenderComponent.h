#pragma once
#include "Game/Public/Component/RenderComponent.h"
#include "Game/Public/Component/TransformComponent.h"

class BoxRenderComponent : public RenderComponent
{
public:
	BoxRenderComponent() = delete;
	~BoxRenderComponent();

	BoxRenderComponent(std::shared_ptr<GameObject> owner);
	BoxRenderComponent(std::shared_ptr<GameObject> owner, exVector2 mSize);
	BoxRenderComponent(std::shared_ptr<GameObject> owner, exVector2 mSize, exColor color);
	BoxRenderComponent(std::shared_ptr<GameObject> owner, exVector2 mSize, exColor color, int layer);

	exVector2 GetSize()const;
	void SetSize(const exVector2 size);

protected:

	virtual void Render(exEngineInterface* inEngineInterface);

private:
	exVector2 mSize;
};

