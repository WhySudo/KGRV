#pragma once
#include "../Mesh.h"
class DefaultRectangle : public Mesh {
public:
	DefaultRectangle() {
		points = new DirectX::XMFLOAT4[8]{
			DirectX::XMFLOAT4(0.1f, 0.1f, 0.5f, 1.0f),	DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f),
			DirectX::XMFLOAT4(-0.1f, -0.1f, 0.5f, 1.0f),	DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f),
			DirectX::XMFLOAT4(0.1f, -0.1f, 0.5f, 1.0f),	DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f),
			DirectX::XMFLOAT4(-0.1f, 0.1f, 0.5f, 1.0f),	DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
		};
		pointCount = 8;
		indeces = new int[6]{ 0,1,2, 1,0,3 };
		indecesCount = 6;
		InitalizeMesh();
	}
};