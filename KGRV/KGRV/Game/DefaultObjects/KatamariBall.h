#pragma once
#include "../GameObject.h"
#include "../Graphics/DefaultMesh/DefaultTexturedCube.h"
#include "../Components/Renderers/LightedTextureMeshRenderer.h"
#include "../Components/MovingBallComponent.h"
#include "../Components/ObjectRotator.h"
#include "../Components/KatamariMovement.h"
#include "../Components/KatamariObjectCapture.h"
class KatamariBall : public GameObject
{

public:
	KatamariBall(GameHandle* handle, PhongData lightData, Texture* drawTexture, TextureLightedShader* shader) : GameObject(handle) {
		view = new GameObject(handle);
		view->transform->position = { .0f, .0f, .0f };

		view->transform->SetParent(transform);

	
		cubeMesh = new DefaultTexturedCube();
		cubeMesh->assignedTexture = drawTexture;
		transform->scale = { 1, 1, 1};
		this->shader = shader;
		capture = new KatamariObjectCapture((GameObject*)this, view->transform, .50f);
		movement = new KatamariMovement((GameObject*)this, view->transform);
		rendererComponent = new LightedTextureMeshRenderer((GameObject*)view, reinterpret_cast<Mesh*>(cubeMesh), shader);
		rendererComponent->phongMaterialData = lightData;
		gameComponents.push_back(movement);
		gameComponents.push_back(capture);
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
	DefaultTexturedCube* cubeMesh;
	KatamariMovement* movement;
	KatamariObjectCapture* capture;
	LightedTextureMeshRenderer* rendererComponent;
	Shader* shader;
};