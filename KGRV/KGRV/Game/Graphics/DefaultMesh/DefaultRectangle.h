#pragma once
#include "../Mesh.h"
class DefaultRectangle : public Mesh {
public:
	DefaultRectangle() {


		auto pushPoints = new DirectX::XMFLOAT4[8]{
			DirectX::XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f),	DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
			DirectX::XMFLOAT4(-0.5f, -0.5f, 0.5f, 1.0f),	DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
			DirectX::XMFLOAT4(0.5f, -0.5f, 0.5f, 1.0f),	DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
			DirectX::XMFLOAT4(-0.5f, 0.5f, 0.5f, 1.0f),	DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
		};
		for (size_t i = 0; i < 8; i++)
		{
			points.push_back(pushPoints[i]);
		}
		delete[] pushPoints;
		pointCount = 8;
		auto pushIndeces = new int[6]{ 0,1,2, 1,0,3 };
		for (size_t i = 0; i < 6; i++)
		{
			indeces.push_back(pushIndeces[i]);
		}
		delete[] pushIndeces;
		indecesCount = 6;
		InitalizeMesh();
	}
};