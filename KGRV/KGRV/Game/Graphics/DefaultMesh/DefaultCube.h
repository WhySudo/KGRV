#pragma once
#include "../Mesh.h"
class DefaultCube : public Mesh {
public:
	DefaultCube() {
		points = new DirectX::XMFLOAT4[16]{
			DirectX::XMFLOAT4(-0.5, -0.5, -0.5, 1.0f),	DirectX::XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f),
			DirectX::XMFLOAT4(0.5, -0.5, -0.5, 1.0f),	DirectX::XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f),
			DirectX::XMFLOAT4(0.5, 0.5, -0.5, 1.0f),	DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f),
			DirectX::XMFLOAT4(-0.5, 0.5, -0.5, 1.0f),	DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f),
			DirectX::XMFLOAT4(-0.5, 0.5, 0.5, 1.0f),	DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f),
			DirectX::XMFLOAT4(0.5, 0.5, 0.5, 1.0f),		DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f),
			DirectX::XMFLOAT4(0.5, -0.5, 0.5, 1.0f),	DirectX::XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f),
			DirectX::XMFLOAT4(-0.5, -0.5, 0.5, 1.0f),	DirectX::XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f),
			
		};
		pointCount = 16;
		indeces = new int[36] {
				0, 2, 1, //face front
				0, 3, 2,
				2, 3, 4, //face top
				2, 4, 5,
				1, 2, 5, //face right
				1, 5, 6,
				0, 7, 4, //face left
				0, 4, 3,
				5, 4, 7, //face back
				5, 7, 6,
				0, 6, 7, //face bottom
				0, 1, 6
		};
		indecesCount = 36;
		InitalizeMesh();
	}
};