#pragma once
#include <DirectXMath.h>
#include <d3d.h>
#include <d3d11.h>
#include <vector>
#include "../Assets/Texture.h"
struct Vertex {
	Vertex() {}
	Vertex(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT2 uv, DirectX::XMFLOAT3 normal) : position(pos.x, pos.y, pos.z, 1), texturePos(uv.x, uv.y), normal(normal.x, normal.y, normal.z, 0) {}
	Vertex(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT2 uv) : position(pos.x, pos.y, pos.z, 1), texturePos(uv.x, uv.y) {}
	Vertex(DirectX::XMFLOAT3 pos) : position(pos.x, pos.y, pos.z, 1), texturePos(0, 0) {}

	DirectX::XMFLOAT4 position = { 0,0,0,1 };
	DirectX::XMFLOAT2 texturePos = { 0, 0 };
	DirectX::XMFLOAT4 normal = { 0,0,0,0 };

};
struct VertexWithColor
{
	VertexWithColor(DirectX::XMFLOAT4 position) : position(position), color(1.0f, 1.0f, 1.0f) {}
	VertexWithColor(DirectX::XMFLOAT4 position, DirectX::XMFLOAT3 color) : position(position), color(color) {}
	VertexWithColor(DirectX::XMFLOAT3 position, DirectX::XMFLOAT3 color) : position(position.x, position.y, position.z, 1.0f), color(color) {}

	DirectX::XMFLOAT4 position = { 0,0,0,1 };
	DirectX::XMFLOAT3 color;
};

class Mesh {
public:
	Mesh() {
	}

	std::vector<DirectX::XMFLOAT4> points;
	std::vector<Vertex> vertex;



	std::vector<int> indeces;
	Texture* assignedTexture;


	//DirectX::XMFLOAT4* points = nullptr;
	//int* indeces = nullptr;

	int pointCount;
	int indecesCount;
	D3D11_BUFFER_DESC vertexBufDesc;
	D3D11_SUBRESOURCE_DATA vertexData;
	D3D11_BUFFER_DESC indexBufDesc;
	D3D11_SUBRESOURCE_DATA indexData;
	D3D11_DEPTH_STENCIL_DESC dsDesc;
	D3D_PRIMITIVE_TOPOLOGY topology;

	bool initialized = false;
	bool textured = false;
	void Legacy_CopyPoints() {
		if (!textured) {
			for (int i = 0; i < points.size(); i += 2)
			{
				DirectX::XMFLOAT3 pos = {0, 0, 0};
				pos.x = points[i].x;
				pos.y = points[i].y;
				pos.z = points[i].z;
				vertex.push_back(Vertex(pos));
			}
		}
	}


	virtual void InitalizeMesh(bool useVertexData = false) {
		textured = useVertexData;
		vertexBufDesc = {};
		vertexData = {};
		indexBufDesc = {};
		indexData = {};

		vertexBufDesc.Usage = D3D11_USAGE_DEFAULT;
		vertexBufDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vertexBufDesc.CPUAccessFlags = 0;
		vertexBufDesc.MiscFlags = 0;
		vertexBufDesc.StructureByteStride = 0;
		if (!useVertexData) {
			vertexBufDesc.ByteWidth = sizeof(DirectX::XMFLOAT4) * pointCount;
		}
		else {
			vertexBufDesc.ByteWidth = sizeof(Vertex) * pointCount;
		}
		if (!useVertexData) {
			vertexData.pSysMem = points.data();
		}
		else {
			vertexData.pSysMem = vertex.data();
		}
		vertexData.SysMemPitch = 0;
		vertexData.SysMemSlicePitch = 0;

		indexBufDesc.Usage = D3D11_USAGE_DEFAULT;
		indexBufDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		indexBufDesc.CPUAccessFlags = 0;
		indexBufDesc.MiscFlags = 0;
		indexBufDesc.StructureByteStride = 0;
		indexBufDesc.ByteWidth = sizeof(int) * indecesCount;



		indexData.pSysMem = indeces.data();
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

		this->topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
		initialized = true;
		Legacy_CopyPoints();
	}

	
	~Mesh() {
		//if (points != nullptr) {
		//	delete points;
		//}
		//if (indeces != nullptr) {
		//	delete indeces;
		//}
	}
};