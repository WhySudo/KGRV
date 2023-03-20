#pragma once
#include "../Mesh.h"
class DefaultCube : public Mesh {
public:

	DefaultCube(Vector4 customColor = { 1.0f, 1.0f, 1.0f, 1.0f }) {
		points.push_back(DirectX::XMFLOAT4(-0.5, -0.5, -0.5, 1.0f));
		points.push_back(customColor);
		points.push_back(DirectX::XMFLOAT4(0.5, -0.5, -0.5, 1.0f));
		points.push_back(customColor);
		points.push_back(DirectX::XMFLOAT4(0.5, 0.5, -0.5, 1.0f));
		points.push_back(customColor);
		points.push_back(DirectX::XMFLOAT4(-0.5, 0.5, -0.5, 1.0f));
		points.push_back(customColor);
		points.push_back(DirectX::XMFLOAT4(-0.5, 0.5, 0.5, 1.0f));
		points.push_back(customColor);
		points.push_back(DirectX::XMFLOAT4(0.5, 0.5, 0.5, 1.0f));
		points.push_back(customColor);
		points.push_back(DirectX::XMFLOAT4(0.5, -0.5, 0.5, 1.0f));
		points.push_back(customColor);
		points.push_back(DirectX::XMFLOAT4(-0.5, -0.5, 0.5, 1.0f));
		points.push_back(customColor);

		pointCount = 16;
		auto pushIndeces = new int[36] {
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
		for (size_t i = 0; i < 36; i++)
		{
			indeces.push_back(pushIndeces[i]);
		}
		delete[] pushIndeces;
		indecesCount = 36;
		InitalizeMesh();
	}
};