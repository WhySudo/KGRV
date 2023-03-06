#pragma once
#include "ObjectComponent.h"
class MovingPlatform: public ObjectComponent
{
public:
	MovingPlatform(GameObject* obj, Vector2 movingBounds, Keys upKey, Keys downKey) : ObjectComponent(obj) {
		this->movingBounds = movingBounds;
		this->upKey = upKey;
		this->downKey = downKey;

	}

	// Унаследовано через ObjectComponent
	virtual void Update(float deltaTime) override;
	virtual bool Initialization() override;

private:
	Vector2 movingBounds;
	Keys upKey;
	Keys downKey;
};

