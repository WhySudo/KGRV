#pragma once
#include "../Mesh.h"
class DefaultCube : public Mesh {
public:
	DefaultCube() {
		points = new DirectX::XMFLOAT4[16]{
			DirectX::XMFLOAT4(-0.5, -0.5, -0.5, 1.0f),	DirectX::XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f),
			DirectX::XMFLOAT4(-0.5, -0.5, 0.5, 1.0f),	DirectX::XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f),
			DirectX::XMFLOAT4(-0.5, 0.5, -0.5, 1.0f),	DirectX::XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f),
			DirectX::XMFLOAT4(-0.5, 0.5, 0.5, 1.0f),	DirectX::XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f),
			DirectX::XMFLOAT4(0.5, -0.5, -0.5, 1.0f),	DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
			DirectX::XMFLOAT4(0.5, -0.5, 0.5, 1.0f),	DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
			DirectX::XMFLOAT4(0.5, 0.5, -0.5, 1.0f),	DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
			DirectX::XMFLOAT4(0.5, 0.5, 0.5, 1.0f),		DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
			
		};
		pointCount = 16;
		indeces = new int[36] {
			0, 1, 3,
			2, 0, 3,

			2, 6, 7,
			2, 7, 3,

			1, 5, 7,
			1, 7, 3,

			7, 5, 4,
			7, 4, 6,

			0, 4, 6,
			0, 6, 2,

			0, 1, 4,
			0, 4, 5};
		indecesCount = 36;
		InitalizeMesh();
	}
};