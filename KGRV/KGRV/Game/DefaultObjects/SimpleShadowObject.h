#pragma once
#include "../GameObject.h"
#include "../Graphics/DefaultMesh/DefaultCube.h"
#include "../Components/Renderers/ShadowMeshRenderer.h"
#include "../Components/MovingBallComponent.h"
#include "../Components/ObjectRotator.h"
#include "../Graphics/Shaders/TextureLightedShader.h"
#include "../Graphics/DefaultMesh/DefaultTexturedCube.h"
class SimpleShadowObject : public GameObject
{

public:
	SimpleShadowObject(GameHandle* handle, ShadowShader* shader, Texture* assignedTexture) : GameObject(handle) {
		cubeMesh = new DefaultTexturedCube();
		cubeMesh->assignedTexture = assignedTexture;
		transform->scale = { 1, 1, 1, 1 };
		this->shader = shader;
		rendererComponent = new ShadowMeshRenderer((GameObject*)this, reinterpret_cast<Mesh*>(cubeMesh), shader);
		gameComponents.push_back(rendererComponent);
		rendererComponent->phongMaterialData.ambient = 0.3f;
		rendererComponent->phongMaterialData.difuse = 0.5f;
		rendererComponent->phongMaterialData.specularAbsorption = 0.5f;
		rendererComponent->phongMaterialData.specularShininess = 10;
	}
	~SimpleShadowObject() {
		delete cubeMesh;
		delete rendererComponent;
	}
private:
	DefaultTexturedCube* cubeMesh;
	ShadowShader* shader;
	ShadowMeshRenderer* rendererComponent;
};