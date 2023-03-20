#pragma once
#include "ObjectComponent.h"
#include "KatamariObject.h"

class KatamariMovement: public ObjectComponent
{
public:
	KatamariMovement(GameObject* obj, Transform* viewTransform = nullptr) :ObjectComponent(obj) {
		this->viewTransform = viewTransform;
	}
	// Унаследовано через ObjectComponent
	virtual void Update(float deltaTime) override;
	virtual bool Initialization() override;

private:
	Transform* viewTransform = nullptr;
	float maxSpeedMovement = 5.0f;
	float acceleration = 9.0f;
	float currentSpeed = -1.0f;
	Vector3 lastDirection = { 0.0f, 0.0f, 1.0f };
	float moveSphereRadius = 1.0f;

	void CalculateMovementFromInput(float deltaTime);
	void ProcessMovement(float deltaTime);

};

