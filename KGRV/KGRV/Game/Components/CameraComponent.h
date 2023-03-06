#pragma once
#include "ObjectComponent.h"
using namespace DirectX;

class CameraComponent : public ObjectComponent
{
public:
	CameraComponent(GameObject* object) : ObjectComponent(object) {
		viewMatrix = {};
		projectionMatrix = {};
		SetPerspectiveProjectionValues(90, object->gameHandle->gameWindow->width / object->gameHandle->gameWindow->height, 0.1, 1000);

	}
	~CameraComponent() {

	}
	virtual void Update(float deltaTime) override;
	virtual bool Initialization() override;

	void SetPerspectiveProjectionValues(float fovDegrees, float aspectRatio, float nearZ, float farZ);
	void SetOrthographicProjectionValues(float width, float height, float nearZ, float farZ);

	void LookAt(XMFLOAT3 target);
	XMMATRIX ViewMatrix() {
		return viewMatrix;
	}
	XMMATRIX ProjectionMatrix() {
		return projectionMatrix;
	}
private:
	void UpdateViewMatrix();

	XMMATRIX viewMatrix = {};
	XMMATRIX projectionMatrix = {};
};

