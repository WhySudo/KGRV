#pragma once
#include "../GameObject.h"
#include "../Components/CameraComponent.h"
#include "../Components/InputCameraComponent.h"
class BaseCameraObject : public GameObject {
public:

	CameraComponent* GetCamera() {
		return camera;
	}
	BaseCameraObject(GameHandle* handle) : GameObject(handle) {
		camera = new CameraComponent((GameObject*)this);
		movement = new InputCameraComponent((GameObject*)this);
		gameComponents.push_back(camera);
		gameComponents.push_back(movement);
	}
	~BaseCameraObject() {
		delete camera;
		delete movement;
	}
private:
	InputCameraComponent* movement;
	CameraComponent* camera;
};