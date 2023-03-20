#pragma once
#include "ObjectComponent.h"
#include <iostream>
#include "../ThirdParty/SimpleMath.h"
using namespace DirectX::SimpleMath;
class WallComponent: public ObjectComponent
{
public:
	Vector2 normal = {1, 0};


	DirectX::BoundingBox* boundingBox;



	WallComponent(GameObject* obj, Vector2 normale):ObjectComponent(obj) {
		normal = normale;
		DirectX::XMFLOAT3 pos = { gameObject->transform->position.x, gameObject->transform->position.y, gameObject->transform->position.z };
		DirectX::XMFLOAT3 scale = { gameObject->transform->scale.x, gameObject->transform->scale.y, gameObject->transform->scale.z };
		
		boundingBox = new DirectX::BoundingBox(pos, scale / 2);
	}
	bool CheckIntersection(Vector2 targetPoint, Vector2 &intersectionPoint) {

		//Rectangle rect = { gameObject->transform->position.x, gameObject->transform->position.y, gameObject->transform->scale.x, gameObject->transform->scale.y };

	}
	virtual Vector2 CalculateReflection(Vector2 touchPoint, Vector2 inputDirection) {
		Vector2 result;
		Vector2::Reflect(inputDirection, normal, result);
		return result;
	}

	// Унаследовано через ObjectComponent
	virtual void Update(float deltaTime) override;
	virtual bool Initialization() override;
};

