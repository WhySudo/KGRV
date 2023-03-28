#pragma once
#include "../GameObject.h"
#include "../Graphics/DefaultMesh/DefaultCube.h"
#include "../Components/Renderers/MeshRenderer.h"
#include "../Components/MovingBallComponent.h"
#include "../Components/ObjectRotator.h"
class SimpleCubeObject : public GameObject
{

public:
	SimpleCubeObject(GameHandle* handle, Shader* shader) : GameObject(handle) {
		cubeMesh = new DefaultCube({.5f, .5f, .5f, 1.0f});
		transform->scale = { 1, 1, 1, 1 };
		this->shader = shader;
		rendererComponent = new MeshRenderer((GameObject*)this, reinterpret_cast<Mesh*>(cubeMesh), shader);
		gameComponents.push_back(rendererComponent);
	}
	~SimpleCubeObject() {
		delete cubeMesh;
		delete rendererComponent;
	}
private:
	DefaultCube* cubeMesh;
	Shader* shader;
	MeshRenderer* rendererComponent;
};