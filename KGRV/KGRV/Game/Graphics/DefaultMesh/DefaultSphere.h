#pragma once
#include "../Mesh.h"
class DefaultSphere : public Mesh {
public:
	DefaultSphere() {
		points = new DirectX::XMFLOAT4[24]{
			DirectX::XMFLOAT4(0, 0.809015, 0.5, 1.0f),	DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
			DirectX::XMFLOAT4(0, -0.809015, 0.5, 1.0f),	DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
			DirectX::XMFLOAT4(0, 0.809015, -0.5, 1.0f),	DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
			DirectX::XMFLOAT4(0, -0.809015, -0.5, 1.0f),	DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),

			DirectX::XMFLOAT4(0.809015, 0, 0.5, 1.0f),	DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
			DirectX::XMFLOAT4(-0.809015, 0, 0.5, 1.0f),	DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
			DirectX::XMFLOAT4(0.809015, 0, -0.5, 1.0f),	DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
			DirectX::XMFLOAT4(-0.809015, 0, -0.5, 1.0f),	DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),


			DirectX::XMFLOAT4(0.5, 0, 0.809015, 1.0f),	DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
			DirectX::XMFLOAT4(-0.5,0, 0.809015, 1.0f),	DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
			DirectX::XMFLOAT4( 0.5,0, -0.809015, 1.0f),	DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
			DirectX::XMFLOAT4( -0.5, 0,-0.809015, 1.0f),	DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
			

		};
		pointCount = 24;
		indeces = new int[60] {
			
		};
		indecesCount = 60;
		InitalizeMesh();
	}
};
