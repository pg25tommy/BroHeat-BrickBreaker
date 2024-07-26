#include "Game/Public/GameObject.h"
#include "Game/Public/Utils.h"

GameObject::GameObject()
{
	LOG("GameOnject created");
}

GameObject::~GameObject()
{
	LOG("GameOnject destroyed");
}

void GameObject::BeginPlay()
{
	LOG("on begin");
}

void GameObject::EndPlay()
{
	LOG("on end");
}

void GameObject::Tick(float deltaTime)
{
	LOG("tick");
}
