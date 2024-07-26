#pragma once
#include "Utils.h"

class GameObject;

class Component
{
	friend GameObject;
public:
	Component() = delete;
	virtual ~Component();

	Component(std::shared_ptr<GameObject> inOwner);


protected:
	//store the owing Game Object
	std::weak_ptr<GameObject> mOwner;

	virtual void InitializeComponent() = 0;
};

typedef std::vector<std::shared_ptr<Component>> ComponentList;
