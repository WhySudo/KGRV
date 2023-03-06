#pragma once
#include "3rdParty/SimpleMath.h"

using namespace DirectX;

class Transform
{
public:
	DirectX::SimpleMath::Vector4 position;
	DirectX::SimpleMath::Vector4 rotation;

	DirectX::SimpleMath::Quaternion rotation_quaternion;

	DirectX::SimpleMath::Vector4 scale = {1, 1, 1, 1};

	const XMVECTOR DEFAULT_FORWARD_VECTOR = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	const XMVECTOR DEFAULT_UP_VECTOR = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	const XMVECTOR DEFAULT_LEFT_VECTOR = XMVectorSet(-1.0f, 0.0f, 0.0f, 0.0f);

	XMVECTOR forward;
	XMVECTOR left;
	XMVECTOR up;

	DirectX::XMMATRIX GlobalPosMatrix();

	void LookAt(XMFLOAT3 target);
	void UpdateValues();

};
struct TransformConstantBuffer
{
	DirectX::XMMATRIX matrix;
};



