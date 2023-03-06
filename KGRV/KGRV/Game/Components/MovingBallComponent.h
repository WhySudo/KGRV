#pragma once
#include "ObjectComponent.h"
#include "../3rdParty/SimpleMath.h"
class MovingBallComponent: public ObjectComponent
{
public:
	MovingBallComponent(GameObject* object) : ObjectComponent(object) {

	}
	// Унаследовано через ObjectComponent
	virtual void Update(float deltaTime) override;
	virtual bool Initialization() override;
	DirectX::SimpleMath::Vector2 direction = {1, 0.5};
	float speed = 0.4;
};

