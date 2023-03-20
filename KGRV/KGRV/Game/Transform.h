#pragma once
#include "3rdParty/SimpleMath.h"
#include <vector>
#include <iostream>
using namespace std;
using namespace DirectX;
using namespace SimpleMath;

class Transform
{
public:

	Transform* parent;
	std::vector<Transform*> children;

	DirectX::SimpleMath::Vector3 position;
	DirectX::SimpleMath::Vector3 rotation;

	DirectX::SimpleMath::Quaternion rotation_quaternion;

	DirectX::SimpleMath::Vector3 scale = {1, 1, 1};

	const XMVECTOR DEFAULT_FORWARD_VECTOR = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	const XMVECTOR DEFAULT_UP_VECTOR = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	const XMVECTOR DEFAULT_LEFT_VECTOR = XMVectorSet(-1.0f, 0.0f, 0.0f, 0.0f);

	XMVECTOR forward;
	XMVECTOR left;
	XMVECTOR up;

	DirectX::XMMATRIX GlobalPosMatrix();
	void SetParent(Transform* newParent, bool saveLocalPosition = false);
	void LookAt(XMFLOAT3 target);
	void UpdateValues();

	DirectX::XMMATRIX LocalToGlobalMatrix();
	DirectX::XMMATRIX GlobalToLocalMatrix();
	XMMATRIX GlobalToLocalRotationMatrix();
	DirectX::XMMATRIX LocalToGlobalRotationMatrix();
	



	DirectX::XMMATRIX GetLocalToParentMatrix()
	{
		DirectX::XMMATRIX modelToWorld = DirectX::XMMatrixIdentity()
			* DirectX::XMMatrixScaling(scale.x, scale.y, scale.z)
			* DirectX::XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z)
			* DirectX::XMMatrixTranslation(position.x, position.y, position.z);
		return modelToWorld;
	}

	//GetGlobalToLocalRotation()
	SimpleMath::Vector3 GlobalPosition() {
		if (parent == nullptr)
		{
			return position;
		}

		auto globalPos = SimpleMath::Vector3::Transform(position, parent->LocalToGlobalMatrix());
		return  globalPos;

	}
	SimpleMath::Vector3 GlobalRotation() {
		if (parent == nullptr)
		{
			return rotation;
		}

		auto addRotation = Quaternion::CreateFromRotationMatrix(parent->LocalToGlobalRotationMatrix());
		auto globalrotation = addRotation.ToEuler() + rotation;
		return globalrotation;

	}
	void SetGlobalPos(SimpleMath::Vector3 newPos) {
		auto newLocalPosition = SimpleMath::Vector3::Transform(newPos, parent->GlobalToLocalMatrix());
		position = newLocalPosition;
	}
	void SetGlobalRotation(SimpleMath::Vector3 globalRotation) {
		auto addRotation = Quaternion::CreateFromRotationMatrix(parent->GlobalToLocalRotationMatrix());
		rotation = addRotation.ToEuler() + globalRotation;
	}


protected:
	void RemoveChild(Transform* child);
	void AddChild(Transform* child);
};
struct TransformConstantBuffer
{
	DirectX::XMMATRIX matrix;
};



