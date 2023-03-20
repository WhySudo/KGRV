#pragma once
#include "../GameObject.h"
#include "../Graphics/DefaultMesh/DefaultCube.h"
#include "../Components/Renderers/MeshRenderer.h"
#include "../Components/MovingBallComponent.h"
#include "../Components/ObjectRotator.h"
#include "../Components/KatamariMovement.h"
#include "../Components/KatamariObjectCapture.h"
class KatamariBall : public GameObject
{

public:
	KatamariBall(GameHandle* handle, Shader* shader) : GameObject(handle) {
		view = new GameObject(handle);
		view->transform->position = { .0f, .0f, .0f };
		view->transform->SetParent(transform);
		cubeMesh = new DefaultCube({0.0f, 1.0f, 1.0f, 1.0f});
		transform->scale = { 1, 1, 1};
		this->shader = shader;
		capture = new KatamariObjectCapture((GameObject*)this, view->transform, .50f);
		movement = new KatamariMovement((GameObject*)this, view->transform);
		gameComponents.push_back(movement);
		gameComponents.push_back(capture);
		rendererComponent = new MeshRenderer((GameObject*)view, reinterpret_cast<Mesh*>(cubeMesh), shader);
		view->gameComponents.push_back(rendererComponent);
	}

	GameObject* view;
	~KatamariBall() {
		delete view;
		delete movement;
		delete cubeMesh;
		delete rendererComponent;
		delete capture;
	}

private:
	DefaultCube* cubeMesh;
	KatamariMovement* movement;
	KatamariObjectCapture* capture;
	Shader* shader;
	MeshRenderer* rendererComponent;
};