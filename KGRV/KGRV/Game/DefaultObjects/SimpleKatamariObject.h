#pragma once
#include "../GameObject.h"
#include "../Graphics/DefaultMesh/DefaultCube.h"
#include "../Components/MeshRenderer.h"
#include "../Components/MovingBallComponent.h"
#include "../Components/ObjectRotator.h"
#include "../Components/KatamariMovement.h"
#include "../Components/KatamariObject.h"
#include "../Graphics/Tools/FbxMeshImporter.h"
class SimpleKatamariObject : public GameObject
{

public:
	SimpleKatamariObject(GameHandle* handle, Shader* shader, std::string fbxPath = "", float sphereRadius = .5f, float scale = 1.0f) : GameObject(handle) {
		
		view = new GameObject(handle);
		view->transform->SetParent(transform);
		view->transform->scale = { scale, scale, scale, 1.0f};
		if (fbxPath.compare("") != 0){
			cubeMesh = FbxMeshImporter::Import(fbxPath);
		}
		
		if (cubeMesh == nullptr) {
			cubeMesh = new DefaultCube({ 1.0f, 1.0f, 0.0f, 1.0f });
		}
		rendererComponent = new MeshRenderer((GameObject*)view, cubeMesh, shader);
		view->gameComponents.push_back(rendererComponent);
		transform->scale = { 1, 1, 1, 1 };
		this->shader = shader;
		katamari = new KatamariObject((GameObject*)this, sphereRadius);
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
	Mesh* cubeMesh;
	KatamariObject* katamari;
	Shader* shader;
	MeshRenderer* rendererComponent;
};