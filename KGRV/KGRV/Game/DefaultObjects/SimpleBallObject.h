#pragma once
#include "../GameObject.h"
#include "../Graphics/DefaultMesh/DefaultBall.h"
#include "../Components/MeshRenderer.h"
#include "../Components/MovingBallComponent.h"
class SimpleBallObject : public GameObject
{

public:
	SimpleBallObject(GameHandle* handle, Shader* shader) : GameObject(handle) {
		rectangleMesh = new DefaultBall();
		transform->scale = { 0.05, 0.05, 0.05, 0.05 };
		this->shader = shader;
		movingComponent = new MovingBallComponent((GameObject*)this);
		rendererComponent = new MeshRenderer((GameObject*)this, reinterpret_cast<Mesh*>(rectangleMesh), shader);

		gameComponents.push_back(rendererComponent);
		gameComponents.push_back(movingComponent);
	}
	~SimpleBallObject() {
		delete rectangleMesh;
		delete rendererComponent;
	}
private:
	DefaultBall* rectangleMesh;
	Shader* shader;
	MeshRenderer* rendererComponent;
	MovingBallComponent* movingComponent;
};

