#pragma once
#include <DirectXMath.h>
#include <d3d.h>
#include <d3d11.h>
class Mesh {
public:
	Mesh(DirectX::XMFLOAT4* points,	int pointCount, int* indeces, int indecesCount) {
		//TODO: MEMORY
		this->pointCount = pointCount;
		this->indecesCount = indecesCount;
		this->points = new DirectX::XMFLOAT4[pointCount];
		this->indeces = new int[indecesCount];


		memcpy(this->points, points, sizeof(DirectX::XMFLOAT4) * pointCount);
		memcpy(this->indeces, indeces, sizeof(int) * pointCount);

		vertexBufDesc = {};
		vertexData = {};
		indexBufDesc = {};
		indexData = {};

		this->pointCount = pointCount;
		this->points = points;
		this->indeces = indeces;
		this->indecesCount = indecesCount;
	
		vertexBufDesc.Usage = D3D11_USAGE_DEFAULT;
		vertexBufDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vertexBufDesc.CPUAccessFlags = 0;
		vertexBufDesc.MiscFlags = 0;
		vertexBufDesc.StructureByteStride = 0;
		vertexBufDesc.ByteWidth = sizeof(DirectX::XMFLOAT4) * pointCount;

		vertexData.pSysMem = points;
		vertexData.SysMemPitch = 0;
		vertexData.SysMemSlicePitch = 0;

		indexBufDesc.Usage = D3D11_USAGE_DEFAULT;
		indexBufDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		indexBufDesc.CPUAccessFlags = 0;
		indexBufDesc.MiscFlags = 0;
		indexBufDesc.StructureByteStride = 0;
		indexBufDesc.ByteWidth = sizeof(int) * indecesCount;

		indexData.pSysMem = indeces;
		indexData.SysMemPitch = 0;
		indexData.SysMemSlicePitch = 0;
	}
	DirectX::XMFLOAT4* points;
	int* indeces;
	int pointCount;
	int indecesCount;
	D3D11_BUFFER_DESC vertexBufDesc;
	D3D11_SUBRESOURCE_DATA vertexData;
	D3D11_BUFFER_DESC indexBufDesc;
	D3D11_SUBRESOURCE_DATA indexData;
	
	~Mesh() {
		delete points;
		delete indeces;
	}
};