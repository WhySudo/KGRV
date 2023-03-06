#include "CameraComponent.h"
#include <iostream>
void CameraComponent::Update(float deltaTime)
{
	UpdateViewMatrix();
}

bool CameraComponent::Initialization()
{
	SetPerspectiveProjectionValues(90, gameObject->gameHandle->gameWindow->width / gameObject->gameHandle->gameWindow->height, 0.1, 1000);
	return true;
}
void CameraComponent::SetPerspectiveProjectionValues(float fovDegrees, float aspectRatio, float nearZ, float farZ)
{
	float fovRadians = (fovDegrees / 360.0f) * XM_2PI;
	this->projectionMatrix = XMMatrixPerspectiveFovLH(fovRadians, aspectRatio, nearZ, farZ);
}
void CameraComponent::SetOrthographicProjectionValues(float width, float height, float nearZ, float farZ)
{
	this->projectionMatrix = XMMatrixOrthographicLH(width, height, nearZ, farZ);
	//gameObject->game->displayWin->GetClientWidth(), gameObject->game->displayWin->GetClientHeight()
}

void CameraComponent::LookAt(XMFLOAT3 target)
{
	gameObject->transform->LookAt(target);

}

void CameraComponent::UpdateViewMatrix()
{
	gameObject->transform->UpdateValues();
	auto myPosition = gameObject->transform->position;
	Vector4 fwd = gameObject->transform->forward;
	auto myTargetPosition = gameObject->transform->position + fwd;

	auto myRotation = gameObject->transform->rotation;

	auto globalPos = myPosition;

	//Calculate camera rotation matrix
	XMMATRIX camRotationMatrix = XMMatrixRotationRollPitchYawFromVector(myRotation);

	//Calculate unit vector of cam target based off camera forward value transformed by cam rotation matrix
	XMVECTOR camTarget = XMVector3TransformCoord(this->gameObject->transform->DEFAULT_FORWARD_VECTOR, camRotationMatrix);

	//Adjust cam target to be offset by the camera's current position
	camTarget += globalPos;

	//Calculate up direction based on current rotation
	//XMVECTOR upDir = XMVector3TransformCoord(this->gameObject->transform->DEFAULT_UP_VECTOR, camRotationMatrix);

	//Rebuild view matrix
	this->viewMatrix = XMMatrixLookAtLH(globalPos, camTarget, this->gameObject->transform->DEFAULT_UP_VECTOR);

}


