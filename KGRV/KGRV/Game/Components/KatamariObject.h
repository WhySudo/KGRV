#pragma once
#include "ObjectComponent.h"
class KatamariObject : public ObjectComponent
{
public: 
	KatamariObject(GameObject* obj, float sphereRadius = 0.5f) :ObjectComponent(obj){
		sphere = new DirectX::BoundingSphere(gameObject->transform->position, sphereRadius);
		captured = false;
	}
	~KatamariObject()
	{
		delete sphere;
	}
	// Унаследовано через ObjectComponent
	virtual void Update(float deltaTime) override;
	virtual void PhysicsUpdate(float deltaTime) override;
	virtual bool Initialization() override;
	bool IsCaptured() {
		return captured;
	}
	void CaptureObject() {
		captured = true;
	}

	BoundingSphere* sphere;
private:
	bool captured = false;
};

