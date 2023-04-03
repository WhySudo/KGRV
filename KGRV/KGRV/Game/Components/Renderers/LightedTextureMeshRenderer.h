#pragma once
#include "MeshRenderer.h"
#include "../../Graphics/Shaders/TextureLightedShader.h"
#include "ConstantBuffers.h"

class LightedTextureMeshRenderer : public MeshRenderer
{
public:
	LightedTextureMeshRenderer(GameObject* gameObject, Mesh* renderedMesh, TextureLightedShader* drawShader) :MeshRenderer(gameObject, renderedMesh, drawShader) {

	}
	PhongData phongMaterialData;
protected:
	void DrawDepthData(ID3D11DeviceContext* context, DepthShader* depthShader, ID3D11DepthStencilState* depthState) override;
	virtual void DrawObject(ID3D11DeviceContext* context, ID3D11RenderTargetView* targetView, ID3D11DepthStencilState* depthState) override;
	void UpdateConstantBuffers() override;
	void InitBuffers(ID3D11Device* device) override;
	virtual void UpdateLightBuffer();
	virtual void UpdateMaterialBuffer();
	virtual ID3D11Buffer* CreateLightBuffer(ID3D11Device* device);
	virtual ID3D11Buffer* CreateMaterialBuffer(ID3D11Device* device);
	ID3D11Buffer* lightBuffer;
	ID3D11Buffer* materialBuffer;

};

