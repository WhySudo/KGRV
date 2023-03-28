#pragma once
#include "../ObjectComponent.h"
class DirectionLight: public ObjectComponent
{
public:
	DirectionLight(GameObject* obj) : ObjectComponent(obj) {

	}

	float inencity = 1.0f;
	XMFLOAT3 lightColor = {1.0f, 1.0f, 1.0f};
	Vector3 ColorIntencity() {
		return lightColor * inencity;
	}

	// Унаследовано через ObjectComponent
	virtual void Update(float deltaTime) override;
	virtual bool Initialization() override;
};

