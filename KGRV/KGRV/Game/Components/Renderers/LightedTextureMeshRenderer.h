#pragma once
#include "MeshRenderer.h"
#include "../../Graphics/Shaders/TextureLightedShader.h"

struct PhongData {
	float ambient = 0.05f;
	float difuse = 0.01f;
	float specularAbsorption = 0.5f;
	float specularShininess = 32.0f;
};

class LightedTextureMeshRenderer : public MeshRenderer
{
public:
	LightedTextureMeshRenderer(GameObject* gameObject, Mesh* renderedMesh, TextureLightedShader* drawShader) :MeshRenderer(gameObject, renderedMesh, drawShader) {

	}
	PhongData phongMaterialData;
protected:
	void DrawObject(ID3D11DeviceContext* context, ID3D11RenderTargetView* targetView, ID3D11DepthStencilState* depthState) override;
	void UpdateConstantBuffers() override;
	void InitBuffers(ID3D11Device* device) override;
	virtual void UpdateLightBuffer();
	virtual void UpdateMaterialBuffer();
	virtual ID3D11Buffer* CreateLightBuffer(ID3D11Device* device);
	virtual ID3D11Buffer* CreateMaterialBuffer(ID3D11Device* device);
	ID3D11Buffer* lightBuffer;
	ID3D11Buffer* materialBuffer;

};

