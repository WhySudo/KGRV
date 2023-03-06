#pragma once
#include <DirectXMath.h>
#include <d3d.h>
#include <d3d11.h>
class Mesh {
public:
	Mesh(DirectX::XMFLOAT4* points,	int pointCount, int* indeces, int indecesCount) {
		//TODO: DEPRECATED
		this->pointCount = pointCount;
		this->indecesCount = indecesCount;
		this->points = new DirectX::XMFLOAT4[pointCount];
		this->indeces = new int[indecesCount];


		memcpy(this->points, points, sizeof(DirectX::XMFLOAT4) * pointCount);
		memcpy(this->indeces, indeces, sizeof(int) * pointCount);
		InitalizeMesh();
	}
	Mesh() {
	}
	DirectX::XMFLOAT4* points = nullptr;
	int* indeces = nullptr;
	int pointCount;
	int indecesCount;
	D3D11_BUFFER_DESC vertexBufDesc;
	D3D11_SUBRESOURCE_DATA vertexData;
	D3D11_BUFFER_DESC indexBufDesc;
	D3D11_SUBRESOURCE_DATA indexData;
	D3D11_DEPTH_STENCIL_DESC dsDesc;
	

	void InitalizeMesh() {
		vertexBufDesc = {};
		vertexData = {};
		indexBufDesc = {};
		indexData = {};

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


		// Depth test parameters
		dsDesc.DepthEnable = true;
		dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		dsDesc.DepthFunc = D3D11_COMPARISON_LESS;

		// Stencil test parameters
		dsDesc.StencilEnable = true;
		dsDesc.StencilReadMask = 0xFF;
		dsDesc.StencilWriteMask = 0xFF;

		// Stencil operations if pixel is front-facing
		dsDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		dsDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
		dsDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		dsDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

		// Stencil operations if pixel is back-facing
		dsDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		dsDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
		dsDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		dsDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	
	}
	~Mesh() {
		if (points != nullptr) {
			delete points;
		}
		if (indeces != nullptr) {
			delete indeces;
		}
	}
};