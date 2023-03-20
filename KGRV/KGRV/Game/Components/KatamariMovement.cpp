#include "KatamariMovement.h"
#include "CameraComponent.h"
#include <iostream>
void KatamariMovement::Update(float deltaTime)
{
	CalculateMovementFromInput(deltaTime);
	ProcessMovement(deltaTime);
}

bool KatamariMovement::Initialization()
{
	return false;
}

void KatamariMovement::CalculateMovementFromInput(float deltaTime)
{
	auto camera = gameObject->gameHandle->loadedScene->currentCamera->gameObject->transform;
	Vector3 forward = camera->forward;
	forward.y = 0;
	forward.Normalize();

	Vector3 normal = { 0,1,0 };
	Vector3 right = normal.Cross(forward);
	auto inputDevice = gameObject->gameHandle->inputDevice;
	if (inputDevice->IsKeyDown(Keys::Z)) {
		return;
	}
	XMVECTOR direction = { 0.0f, 0.0f, 0.0f };
	bool anyMovement = false;
	if (inputDevice->IsKeyDown(Keys::Up)) {
		direction += forward;
		anyMovement = true;
	}
	if (inputDevice->IsKeyDown(Keys::Down)) {
		direction -= forward;
		anyMovement = true;
	}
	if (inputDevice->IsKeyDown(Keys::Left)) {
		direction -= right;
		anyMovement = true;
	}
	if (inputDevice->IsKeyDown(Keys::Right)) {
		direction += right;
		anyMovement = true;
	}

	Vector3 dir = direction;
	dir.Normalize();
	direction = dir;
	if (dir.LengthSquared() > 0.5f) {
		lastDirection = direction;
	}
	else {
		anyMovement = false;
	}

	if (anyMovement) {
		currentSpeed += acceleration * deltaTime;
		if (currentSpeed >= maxSpeedMovement) {
			currentSpeed = maxSpeedMovement;
		}
		
	}
	else {
		currentSpeed -= acceleration * deltaTime;
		if (currentSpeed <= 0.0f) {
			currentSpeed = 0.0f;
		}
	}
}

void KatamariMovement::ProcessMovement(float deltaTime)
{

	if (currentSpeed <= 0) {
		return;
	}
	auto radRotationAngle = currentSpeed * deltaTime / moveSphereRadius;
	if (viewTransform != nullptr) {
		Vector3 normal = { 0,1,0 };
		Vector3 rotationAxis = normal.Cross(lastDirection);
		auto rot = Quaternion::CreateFromAxisAngle(rotationAxis, radRotationAngle);
		auto quat_view = Quaternion::CreateFromRotationMatrix(viewTransform->GetLocalToParentMatrix()) * rot;
		viewTransform->rotation = quat_view.ToEuler();
		//viewTransform->rotation;
	}
	gameObject->transform->position += lastDirection * deltaTime * currentSpeed;
}
