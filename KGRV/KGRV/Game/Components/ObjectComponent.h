#pragma once

#include "../GameObject.h"
class GameObject;
class ObjectComponent
{
public:
	GameObject* gameObject;
	ObjectComponent(GameObject* gameObject);
	virtual void Draw() = 0;
	virtual void Update(float deltaTime) = 0;
	bool Initialize() {
		isInitialized = Initialization();
		return isInitialized;
	}

	bool IsInitialized() {
		return	isInitialized;
	}
protected:
	bool isInitialized;

	virtual bool Initialization() = 0;


};

