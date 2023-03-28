#pragma once
#include "../GameObject.h"
#include "../Graphics/DefaultMesh/DefaultTexturedCube.h"
#include "../Components/Renderers/LightedTextureMeshRenderer.h"
#include "../Components/MovingBallComponent.h"
#include "../Components/ObjectRotator.h"
#include "../Components/KatamariMovement.h"
#include "../Components/KatamariObject.h"
#include "../Graphics/Tools/FbxMeshImporter.h"
class TexturedLightedKatamariObject : public GameObject
{

public:
	TexturedLightedKatamariObject(GameHandle* handle, TextureLightedShader* shader, std::string fbxPath = "", float sphereRadius = .5f, float scale = 1.0f, Texture* renderTex = nullptr) : GameObject(handle) {

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
		rendererComponent = new LightedTextureMeshRenderer((GameObject*)view, cubeMesh, shader);
		view->gameComponents.push_back(rendererComponent);
		transform->scale = { 1, 1, 1, 1 };
		this->shader = shader;
		katamari = new KatamariObject((GameObject*)this, sphereRadius);
		gameComponents.push_back(katamari);

	}

	GameObject* view;
	Texture* tex;
	LightedTextureMeshRenderer* rendererComponent;
	~TexturedLightedKatamariObject() {
		delete view;
		delete cubeMesh;
		delete rendererComponent;
		delete katamari;
	}

private:
	Mesh* cubeMesh;
	KatamariObject* katamari;
	TextureLightedShader* shader;
};