#pragma once
#include "../GameObject.h"
#include "../Graphics/DefaultMesh/DefaultCube.h"
#include "../Components/MeshRenderer.h"
#include "../Components/MovingBallComponent.h"
#include "../Components/ObjectRotator.h"
#include "../Components/KatamariMovement.h"
#include "../Components/KatamariObject.h"
class SimpleKatamariObject : public GameObject
{

public:
	SimpleKatamariObject(GameHandle* handle, Shader* shader) : GameObject(handle) {
		cubeMesh = new DefaultCube({ 1.0f, 1.0f, 0.0f, 1.0f });
		transform->scale = { 1, 1, 1, 1 };
		this->shader = shader;
		rendererComponent = new MeshRenderer((GameObject*)this, reinterpret_cast<Mesh*>(cubeMesh), shader);
		katamari = new KatamariObject((GameObject*)this);
		gameComponents.push_back(rendererComponent);
		gameComponents.push_back(katamari);
	}

	GameObject* view;
	~SimpleKatamariObject() {
		delete view;
		delete cubeMesh;
		delete rendererComponent;
		delete katamari;
	}

private:
	DefaultCube* cubeMesh;
	KatamariObject* katamari;
	Shader* shader;
	MeshRenderer* rendererComponent;
};