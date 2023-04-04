#pragma once
#include "../GameObject.h"
#include "../Graphics/DefaultMesh/DefaultCube.h"
#include "../Components/Renderers/ShadowMeshRenderer.h"
#include "../Components/Renderers/LightedTextureMeshRenderer.h"
#include "../Components/MovingBallComponent.h"
#include "../Components/ObjectRotator.h"
#include "../Graphics/Shaders/TextureLightedShader.h"
#include "../Graphics/DefaultMesh/DefaultTexturedCube.h"
class SimpleShadowObject : public GameObject
{

public:
	SimpleShadowObject(GameHandle* handle, ShadowShader* shader, Texture* assignedTexture, TextureLightedShader* extraShader = nullptr) : GameObject(handle) {
		cubeMesh = new DefaultTexturedCube();
		cubeMesh->assignedTexture = assignedTexture;
		transform->scale = { 1, 1, 1, 1 };
		this->shader = shader;
		rendererComponent = new ShadowMeshRenderer((GameObject*)this, reinterpret_cast<Mesh*>(cubeMesh), shader);
		//rendererComponent2 = new LightedTextureMeshRenderer((GameObject*)this, reinterpret_cast<Mesh*>(cubeMesh), extraShader);
		gameComponents.push_back(rendererComponent);
//		gameComponents.push_back(rendererComponent2);
		rendererComponent->phongMaterialData.ambient = 0.3f;
		rendererComponent->phongMaterialData.difuse = 0.1;
		rendererComponent->phongMaterialData.specularAbsorption = 1.0f;
		rendererComponent->phongMaterialData.specularShininess = 0;
	}
	~SimpleShadowObject() {
		delete cubeMesh;
		delete rendererComponent;
		//delete rendererComponent2;
	}
private:
	DefaultTexturedCube* cubeMesh;
	ShadowShader* shader;
	ShadowMeshRenderer* rendererComponent;
	LightedTextureMeshRenderer* rendererComponent2;
};