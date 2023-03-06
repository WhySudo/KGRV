#pragma once
#include "ObjectComponent.h"
class InputCameraComponent : public ObjectComponent
{
public:
	InputCameraComponent(GameObject* gameObject) : ObjectComponent(gameObject)
	{
	}

	void Draw() override;
	void Update(float deltaTime) override;

protected:
	bool Initialization() override;
};

