#pragma once
#include "Game/Public/Component.h"
#include "Engine/Public/EngineTypes.h"


class TransformComponent : public Component
{
public:
	TransformComponent() = delete;
	~TransformComponent();

	TransformComponent(std::shared_ptr<GameObject> owner, exVector2 position, exVector2 scale, exVector2 rotation);
	TransformComponent(std::shared_ptr<GameObject> owner, exVector2 position);
	TransformComponent(std::shared_ptr<GameObject> owner, exVector2&& position);

	exVector2 GetPosition() const;
	void SetPosition(const exVector2& newPosition);
	void SetRotation(const exVector2& newRotation);
	void SetScale(const exVector2& newScale);

protected:
	virtual void InitializeComponent() override;

private:
	exVector2 mPosition;
	exVector2 mScale;
	exVector2 mRotation;

};

