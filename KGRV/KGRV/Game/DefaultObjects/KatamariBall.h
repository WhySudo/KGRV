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

		
		cubeMesh = new DefaultCube({1.0f, 0.64f, 0.0f, 1.0f});
		transform->scale = { 1, 1, 1};
		this->shader = shader;
		capture = new KatamariObjectCapture((GameObject*)this, view->transform, .50f);
		movement = new KatamariMovement((GameObject*)this, view->transform);
		rendererComponent = new MeshRenderer((GameObject*)view, reinterpret_cast<Mesh*>(cubeMesh), shader);
		gameComponents.push_back(movement);
		gameComponents.push_back(capture);
		view->gameComponents.push_back(rendererComponent);
		/*
		view1 = new GameObject(handle);
		view2 = new GameObject(handle);
		view3 = new GameObject(handle);
		view4 = new GameObject(handle);
		view5 = new GameObject(handle);
		view6 = new GameObject(handle);
		view1->transform->position = { .0f, -.55f, .0f };
		view2->transform->position = { .0f, .55f, .0f };
		view3->transform->position = { -.55f, .0f, .0f };
		view4->transform->position = { .55f, .0f, .0f };
		view5->transform->position = { .0f, .0f, .55f };
		view6->transform->position = { .0f, .0f, -.55f };
		view1->transform->scale = { 0.8f, 0.1f, 0.8f };
		view2->transform->scale = { 0.8f, 0.1f, 0.8f };
		view3->transform->scale = { 0.1f, 0.8f, 0.8f };
		view4->transform->scale = { 0.1f, 0.8f, 0.8f };
		view5->transform->scale = { 0.8f, 0.8f, 0.1f };
		view6->transform->scale = { 0.8f, 0.8f, 0.1f };

		view1->transform->SetParent(view->transform, false);
		view2->transform->SetParent(view->transform, false);
		view3->transform->SetParent(view->transform, false);
		view4->transform->SetParent(view->transform, false);
		view5->transform->SetParent(view->transform, false);
		view6->transform->SetParent(view->transform, false);
		rendererComponent1 = new MeshRenderer((GameObject*)view1, reinterpret_cast<Mesh*>(cubeMesh), shader);
		rendererComponent2 = new MeshRenderer((GameObject*)view2, reinterpret_cast<Mesh*>(cubeMesh), shader);
		rendererComponent3 = new MeshRenderer((GameObject*)view3, reinterpret_cast<Mesh*>(cubeMesh), shader);
		rendererComponent4 = new MeshRenderer((GameObject*)view4, reinterpret_cast<Mesh*>(cubeMesh), shader);
		rendererComponent5 = new MeshRenderer((GameObject*)view5, reinterpret_cast<Mesh*>(cubeMesh), shader);
		rendererComponent6 = new MeshRenderer((GameObject*)view6, reinterpret_cast<Mesh*>(cubeMesh), shader);

		view1->gameComponents.push_back(rendererComponent1);
		view2->gameComponents.push_back(rendererComponent2);
		view3->gameComponents.push_back(rendererComponent3);
		view4->gameComponents.push_back(rendererComponent4);
		view5->gameComponents.push_back(rendererComponent5);
		view6->gameComponents.push_back(rendererComponent6);
		*/
	}

	GameObject* view;
	GameObject* view1;
	GameObject* view2;
	GameObject* view3;
	GameObject* view4;
	GameObject* view5;
	GameObject* view6;
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
	MeshRenderer* rendererComponent1;
	MeshRenderer* rendererComponent2;
	MeshRenderer* rendererComponent3;
	MeshRenderer* rendererComponent4;
	MeshRenderer* rendererComponent5;
	MeshRenderer* rendererComponent6;
};