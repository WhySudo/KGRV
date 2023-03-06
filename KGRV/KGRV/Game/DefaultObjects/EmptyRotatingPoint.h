#pragma once
#include "../GameObject.h"
#include "../Components/RotateAroundComponent.h"
class EmptyRotatingPoint : public GameObject
{

public:
	EmptyRotatingPoint(GameHandle* handle, GameObject* target, Vector3 axis, Vector3 offset, float speed) : GameObject(handle) {
		rotComponent = new RotateAroundComponent((GameObject*)this, target, axis, offset, speed);
		gameComponents.push_back(rotComponent);
	}
	~EmptyRotatingPoint() {
		delete rotComponent;
	}
private:
	RotateAroundComponent* rotComponent;
};

