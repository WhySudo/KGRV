#pragma once
#include "../GameObject.h"
#include "../Components/Light/Light.h"
class DirectionLightObject : public GameObject {
public:
	DirectionLightObject(GameHandle* handle, Vector3 Color = {1.0f, 1.0f, 1.0f}, float intencity = 1.0f) : GameObject(handle) {
		light = new Light((GameObject*)this);
		light->lightColor = Color;
		light->inencity = intencity;
		gameComponents.push_back(light);
	}
	~DirectionLightObject() {
		delete light;
	}
	Light* light;
};