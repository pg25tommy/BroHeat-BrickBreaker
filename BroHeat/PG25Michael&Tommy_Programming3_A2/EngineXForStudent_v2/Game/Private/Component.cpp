#include "Game/Public/Component.h"

Component::~Component()
{
}

Component::Component(std::shared_ptr<GameObject> inOwner)
{
	mOwner = inOwner;
}
