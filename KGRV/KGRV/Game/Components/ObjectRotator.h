#pragma once
#include "ObjectComponent.h"
class ObjectRotator: public ObjectComponent
{
public:
	ObjectRotator(GameObject* obj) : ObjectComponent(obj) {

	}
	// Унаследовано через ObjectComponent
	virtual void Update(float deltaTime) override;
	virtual bool Initialization() override;
	float zRotationSpeed = 3.14159/2;
};

