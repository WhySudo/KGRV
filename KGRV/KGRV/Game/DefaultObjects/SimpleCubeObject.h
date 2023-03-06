#pragma once
#include "../GameObject.h"
#include "../Graphics/DefaultMesh/DefaultCube.h"
#include "../Components/MeshRenderer.h"
#include "../Components/MovingBallComponent.h"
#include "../Components/ObjectRotator.h"
class SimpleCubeObject : public GameObject
{

public:
	SimpleCubeObject(GameHandle* handle, Shader* shader) : GameObject(handle) {
		cubeMesh = new DefaultCube();
		transform->scale = { 1, 1, 1, 1 };
		this->shader = shader;
		rendererComponent = new MeshRenderer((GameObject*)this, reinterpret_cast<Mesh*>(cubeMesh), shader);
		rotator = new ObjectRotator((GameObject*)this);
		gameComponents.push_back(rendererComponent);
		gameComponents.push_back(rotator);
	}
	~SimpleCubeObject() {
		delete cubeMesh;
		delete rendererComponent;
		delete rotator;
	}
private:
	DefaultCube* cubeMesh;
	Shader* shader;
	MeshRenderer* rendererComponent;
	ObjectRotator* rotator;
};