#include "InputCameraComponent.h"
#include <iostream>
using namespace std;
void InputCameraComponent::Draw()
{
}

void InputCameraComponent::Update(float deltaTime)
{
	Vector3 move = {};
	move.x += gameObject->gameHandle->gameWindow->inputDevice->IsKeyDown(Keys::W);
	move.x -= gameObject->gameHandle->gameWindow->inputDevice->IsKeyDown(Keys::S);

	move.y += gameObject->gameHandle->gameWindow->inputDevice->IsKeyDown(Keys::Space);
	move.y -= gameObject->gameHandle->gameWindow->inputDevice->IsKeyDown(Keys::LeftShift);
															 
	move.z += gameObject->gameHandle->gameWindow->inputDevice->IsKeyDown(Keys::D);
	move.z -= gameObject->gameHandle->gameWindow->inputDevice->IsKeyDown(Keys::A);

	auto moveVector = move * 2.0f * deltaTime;

	gameObject->transform->position += moveVector.x * gameObject->transform->forward;
	gameObject->transform->position += moveVector.y * gameObject->transform->DEFAULT_UP_VECTOR;
	gameObject->transform->position += moveVector.z * gameObject->transform->left * -1;

	if (gameObject->gameHandle->gameWindow->inputDevice->IsKeyDown(Keys::Z))
	{
		XMFLOAT2 moveRot = { 0.0, 0.0f };

		moveRot.y -= gameObject->gameHandle->gameWindow->inputDevice->IsKeyDown(Keys::Up) * 3.14159/4 * deltaTime;
		moveRot.y += gameObject->gameHandle->gameWindow->inputDevice->IsKeyDown(Keys::Down) * 3.14159 / 4 * deltaTime;
		moveRot.x -= gameObject->gameHandle->gameWindow->inputDevice->IsKeyDown(Keys::Left) * 3.14159 / 4 * deltaTime;
		moveRot.x += gameObject->gameHandle->gameWindow->inputDevice->IsKeyDown(Keys::Right) * 3.14159 / 4 * deltaTime;

		gameObject->transform->rotation.x += moveRot.y;
		gameObject->transform->rotation.y += moveRot.x;
		gameObject->transform->rotation.z = 0;
	}
	if (gameObject->gameHandle->gameWindow->inputDevice->IsKeyDown(Keys::O)) {

	}
	if (gameObject->gameHandle->gameWindow->inputDevice->IsKeyDown(Keys::P)) {

	}
}

bool InputCameraComponent::Initialization()
{
	return false;
}

