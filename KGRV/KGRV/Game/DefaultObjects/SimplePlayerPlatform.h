#pragma once

#include "../GameObject.h"
#include "../Graphics/DefaultMesh/DefaultRectangle.h"
#include "../Components/MeshRenderer.h"
#include "../Components/RoundWall.h"
#include "../Components/MovingPlatform.h"

class SimplePlayerPlatform : public GameObject
{

public:

	SimplePlayerPlatform(GameHandle* handle, Shader* shader, Vector2 normale, Vector4 pos, Vector4 scale, Keys keyUp, Keys keyDown, Vector2 bounds) : GameObject(handle) {
		rectangleMesh = new DefaultRectangle();
		transform->position = pos;
		transform->scale = scale;
		this->shader = shader;
		wallComponent = new WallComponent((GameObject*)this, normale);
		platform = new MovingPlatform((GameObject*)this, bounds, keyUp, keyDown);

		//wallComponent->normal = normale;
		rendererComponent = new MeshRenderer((GameObject*)this, reinterpret_cast<Mesh*>(rectangleMesh), shader);
		gameComponents.push_back(rendererComponent);
		gameComponents.push_back(wallComponent);
		gameComponents.push_back(platform);
	}
	~SimplePlayerPlatform() {
		delete rectangleMesh;
		delete rendererComponent;
	}
private:
	DefaultRectangle* rectangleMesh;
	Shader* shader;
	MeshRenderer* rendererComponent;
	WallComponent* wallComponent;
	MovingPlatform* platform;
};

#pragma once
