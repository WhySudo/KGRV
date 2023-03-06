#pragma once
#include "../GameObject.h"
#include "../Components/CameraComponent.h"
#include "../Components/InputCameraComponent.h"
#include "../Components/CameraPointsAttachment.h"
class BaseCameraObject : public GameObject {
public:

	CameraComponent* GetCamera() {
		return camera;
	}
	BaseCameraObject(GameHandle* handle) : GameObject(handle) {
		camera = new CameraComponent((GameObject*)this);
		movement = new InputCameraComponent((GameObject*)this);
		attachment = new CameraPointsAttachment((GameObject*)this);
		gameComponents.push_back(camera);
		gameComponents.push_back(movement);
		gameComponents.push_back(attachment);
	}
	~BaseCameraObject() {
		delete camera;
		delete movement;
		delete attachment;
	}
private:
	InputCameraComponent* movement;
	CameraComponent* camera;
public:
	CameraPointsAttachment* attachment;
};