#pragma once

#include "../GameObject.h"
#include "../Graphics/DefaultMesh/DefaultRectangle.h"
#include "../Components/Renderers/MeshRenderer.h"
#include "../Components/WallComponent.h"

class SimpleWallObject: public GameObject
{

public:

	SimpleWallObject(GameHandle* handle, Shader* shader, Vector2 normale, Vector4 pos, Vector4 scale) : GameObject(handle) {
		rectangleMesh = new DefaultRectangle();
		transform->position = (Vector3)pos;
		transform->scale = (Vector3)scale;
		this->shader = shader;
		wallComponent = new WallComponent((GameObject*)this, normale);
		//wallComponent->normal = normale;
		rendererComponent = new MeshRenderer((GameObject*)this, reinterpret_cast<Mesh*>(rectangleMesh), shader);
		gameComponents.push_back(rendererComponent);
		gameComponents.push_back(wallComponent);
	}
	~SimpleWallObject() {
		delete rectangleMesh;
		delete rendererComponent;
	}
private:
	DefaultRectangle* rectangleMesh;
	Shader* shader;
	MeshRenderer* rendererComponent;
	WallComponent* wallComponent;
};

