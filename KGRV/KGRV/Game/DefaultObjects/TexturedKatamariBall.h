#pragma once
#include "../GameObject.h"
#include "../Graphics/DefaultMesh/DefaultTexturedCube.h"
#include "../Components/Renderers/TextureMeshRenderer.h"
#include "../Components/MovingBallComponent.h"
#include "../Components/ObjectRotator.h"
#include "../Components/KatamariMovement.h"
#include "../Components/KatamariObject.h"
#include "../Graphics/Tools/FbxMeshImporter.h"
class TexturedKatamariObject : public GameObject
{

public:
	TexturedKatamariObject(GameHandle* handle, TextureShader* shader, std::string fbxPath = "", float sphereRadius = .5f, float scale = 1.0f, Texture* renderTex = nullptr) : GameObject(handle) {

		view = new GameObject(handle);
		tex = renderTex;
		view->transform->SetParent(transform);
		view->transform->scale = { scale, scale, scale, 1.0f };
		if (fbxPath.compare("") != 0) {
			cubeMesh = FbxMeshImporter::Import(fbxPath, true);
		}
		if (cubeMesh == nullptr) {
			cubeMesh = new DefaultTexturedCube();
		}
		cubeMesh->assignedTexture = tex;
		rendererComponent = new TextureMeshRenderer((GameObject*)view, cubeMesh, shader);
		view->gameComponents.push_back(rendererComponent);
		transform->scale = { 1, 1, 1, 1 };
		this->shader = shader;
		katamari = new KatamariObject((GameObject*)this, sphereRadius);
		gameComponents.push_back(katamari);

	}

	GameObject* view;
	Texture* tex;
	~TexturedKatamariObject() {
		delete view;
		delete cubeMesh;
		delete rendererComponent;
		delete katamari;
	}

private:
	Mesh* cubeMesh;
	KatamariObject* katamari;
	TextureShader* shader;
	TextureMeshRenderer* rendererComponent;
};