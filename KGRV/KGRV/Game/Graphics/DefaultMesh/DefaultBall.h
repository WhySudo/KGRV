#pragma once
#include "../Mesh.h"
class DefaultBall : public Mesh {
public:
	DefaultBall() {
		auto pushPoints = new DirectX::XMFLOAT4[52]{
			DirectX::XMFLOAT4(0, 0, 0, 1.0f),	DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
			DirectX::XMFLOAT4(1.0 / 2, 0.0 / 2, 2.0, 1.0), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
			DirectX::XMFLOAT4(0.866 / 2, 0.4997 / 2, 2.0, 1.0), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
			DirectX::XMFLOAT4(0.500 / 2, 0.8657 / 2, 2.0, 1.0), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
			DirectX::XMFLOAT4(0.000 / 2, 0.9999 / 2, 2.0, 1.0), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
			DirectX::XMFLOAT4(-0.49 / 2, 0.8665 / 2, 2.0, 1.0), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
			DirectX::XMFLOAT4(-0.86 / 2, 0.5011 / 2, 2.0, 1.0), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
			DirectX::XMFLOAT4(-0.99 / 2, 0.0015 / 2, 2.0, 1.0), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
			DirectX::XMFLOAT4(-0.86 / 2, -0.498 / 2, 2.0, 1.0), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
			DirectX::XMFLOAT4(-0.50 / 2, -0.864 / 2, 2.0, 1.0), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
			DirectX::XMFLOAT4(-0.00 / 2, -0.999 / 2, 2.0, 1.0), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
			DirectX::XMFLOAT4(0.497 / 2, -0.867 / 2, 2.0, 1.0), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
			DirectX::XMFLOAT4(0.864 / 2, -0.502 / 2, 2.0, 1.0), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
		};
		for (int i = 0; i < 52; i++) {
			points.push_back(pushPoints[i]);
		}
		delete[] pushPoints;
		pointCount = 52;
		auto pushIndeces = new int[36] {
			0, 1, 2,
			0, 2, 3,
			0, 3, 4,
			0, 4, 5,
			0, 5, 6,
			0, 6, 7,
			0, 7, 8,
			0, 8, 9,
			0, 9, 10,
			0, 10, 11,
				0, 11, 12,
				0, 12, 1};
		indecesCount = 36;
		for (int i = 0; i < 36; i++) {
			indeces.push_back(pushIndeces[i]);
		}
		delete[] pushIndeces;
		InitalizeMesh();
	}
};