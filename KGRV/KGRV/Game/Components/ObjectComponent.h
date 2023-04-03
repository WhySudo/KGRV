#pragma once

#include "../GameObject.h"
class GameObject;
class ObjectComponent
{
public:
	GameObject* gameObject;
	ObjectComponent(GameObject* gameObject);
	virtual void BeforeDraw() {

	}
	virtual void Draw() {

	}
	virtual void PhysicsUpdate(float timeDeltaTime) {

	}
	virtual void BeforeUpdate() {};

	virtual void Update(float deltaTime) = 0;
	virtual void LateUpdate(float deltaTime) {
	
	}
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

