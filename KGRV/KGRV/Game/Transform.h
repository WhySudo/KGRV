#pragma once
#include "3rdParty/SimpleMath.h"

class Transform
{
public:
	DirectX::SimpleMath::Vector4 position;
	DirectX::SimpleMath::Vector4 rotation;
	DirectX::SimpleMath::Vector4 scale = {1, 1, 1, 1};
};
struct TransformConstantBuffer
{
	DirectX::XMMATRIX matrix;
};



