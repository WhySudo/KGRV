#pragma once
#include "../GameObject.h"
#include "../Components/Light/DirectionLight.h"
class DirectionLightObject : public GameObject {
public:
	DirectionLightObject(GameHandle* handle, Vector3 Color = {1.0f, 1.0f, 1.0f}, float intencity = 1.0f) : GameObject(handle) {
		lightComponent = new DirectionLight((GameObject*)this);
		lightComponent->lightColor = Color;
		lightComponent->inencity = intencity;
		gameComponents.push_back(lightComponent);
	}
	~DirectionLightObject() {
		delete lightComponent;
	}

	DirectionLight* lightComponent;

};