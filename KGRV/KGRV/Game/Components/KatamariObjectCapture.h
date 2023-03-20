#pragma once
#include "ObjectComponent.h"
#include <vector>
#include "KatamariObject.h"
class KatamariObjectCapture : public ObjectComponent
{

public:
	KatamariObjectCapture(GameObject* obj, Transform* targetView, float radius) :ObjectComponent(obj){
		sphere = new DirectX::BoundingSphere(gameObject->transform->position, radius);
		this->targetView = targetView;
	}
	~KatamariObjectCapture()
	{
		delete sphere;
	}
	BoundingSphere* sphere;
	vector<KatamariObject*> capturedObjects;
private:
	void SearchForObjectCapture();
	void CaptureObject(KatamariObject* obj);
	Transform* targetView;

	// Унаследовано через ObjectComponent
	virtual void Update(float deltaTime) override;
	virtual bool Initialization() override;
	virtual void PhysicsUpdate(float deltaTime) override;
};

