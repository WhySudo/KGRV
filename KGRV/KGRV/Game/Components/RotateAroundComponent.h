#pragma once
#include "ObjectComponent.h"
class RotateAroundComponent : public ObjectComponent
{
public:
	RotateAroundComponent(GameObject* object, GameObject* targetObject, XMFLOAT3 rotAxis, float speed) : ObjectComponent(object) {
		this->targetObject = targetObject;
		this->rotAxis = rotAxis;
		this->speed = speed;
	}
	// Унаследовано через ObjectComponent
	virtual void Update(float deltaTime) override;
	virtual bool Initialization() override;
	GameObject* targetObject;
protected:
	XMFLOAT3 rotAxis;
	float speed;
	float storedRotation = 0;
};

