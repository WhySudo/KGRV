#pragma once
#include "ObjectComponent.h"
class RotateAroundComponent : public ObjectComponent
{
public:
	RotateAroundComponent(GameObject* object, GameObject* targetObject, Vector3 rotAxis, Vector3 rotVector, float speed) : ObjectComponent(object) {
		this->targetObject = targetObject;
		this->rotAxis = rotAxis;
		this->rotVector = rotVector;
		this->speed = speed;
	}
	// Унаследовано через ObjectComponent
	virtual void Update(float deltaTime) override;
	virtual bool Initialization() override;
	GameObject* targetObject;
protected:
	Vector3 rotAxis;
	Vector3 rotVector;
	float speed;
	float storedRotation = 0;
};

