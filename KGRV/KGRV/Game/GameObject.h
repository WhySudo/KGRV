#pragma once
#include <vector>

#include "Transform.h"
#include "Components/ObjectComponent.h"
#include "3rdParty/SimpleMath.h"
#include "GameHandle.h"

using namespace DirectX::SimpleMath;
class ObjectComponent;
class GameHandle;
class GameObject {

public:
	GameHandle* gameHandle;
	Transform* transform;
	void Draw();
	void Update(float timeDeltaTime);
	void PhysicsUpdate(float timeDeltaTime);
	void Initialize();
	
	GameObject(GameHandle* game) {
		transform = new Transform();
		gameHandle = game;
	}
	~GameObject() {
		delete transform;
	}
	std::vector<ObjectComponent*> gameComponents;

};