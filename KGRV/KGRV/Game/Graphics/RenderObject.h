#pragma once
#include "Mesh.h"
#include "Shader.h"

class RenderObject {
public:
	Mesh* mesh;
	Shader* shader;
	RenderObject(Mesh* mesh,	Shader* shader) {
		this->mesh = mesh;
		this->shader = shader;
	}
	void Initialize(ID3D11Device* device) {
		device->CreateBuffer(&mesh->vertexBufDesc, &mesh->vertexData, &vertexBuffer);
		device->CreateBuffer(&mesh->indexBufDesc, &mesh->indexData, &indexBuffer);
		shader->Initalize(device);
	}

	void DrawObject(ID3D11DeviceContext* context, ID3D11RenderTargetView* targetView) {
		UINT strides[] = { 32 };
		UINT offsets[] = { 0 };
		context->IASetInputLayout(shader->layout);
		context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		context->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
		context->IASetVertexBuffers(0, 1, &vertexBuffer, strides, offsets);
		context->VSSetShader(shader->vertexShader, nullptr, 0);
		context->PSSetShader(shader->pixelShader, nullptr, 0);
		context->OMSetRenderTargets(1, &targetView, nullptr);
		context->DrawIndexed(mesh->indecesCount, 0, 0);
		context->OMSetRenderTargets(0, nullptr, nullptr);

	}
private:
	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;
};