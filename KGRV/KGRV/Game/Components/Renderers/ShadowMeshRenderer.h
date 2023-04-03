#pragma once
//#include "LightedTextureMeshRenderer.h"
#include "MeshRenderer.h"
#include "../../Graphics/Shaders/ShadowShader.h"
#include "ConstantBuffers.h"
class ShadowMeshRenderer :
    public MeshRenderer
{

public:
    ShadowMeshRenderer(GameObject* gameObject, Mesh* renderedMesh, ShadowShader* drawShader) :MeshRenderer(gameObject, renderedMesh, drawShader) {

    }
    ID3D11Buffer* CreateTransformBuffer(ID3D11Device* device) override;
	PhongData phongMaterialData;
	void DrawDepthData(ID3D11DeviceContext* context, DepthShader* depthShader, ID3D11DepthStencilState* depthState) override;

protected:
    void DrawObject(ID3D11DeviceContext* context, ID3D11RenderTargetView* targetView, ID3D11DepthStencilState* depthState) override;
    void UpdateDrawMatrix() override;
	
protected:
	void UpdateConstantBuffers() override;
	void InitBuffers(ID3D11Device* device) override;
	virtual void UpdateLightBuffer();
	virtual void UpdateMaterialBuffer();
	virtual ID3D11Buffer* CreateLightBuffer(ID3D11Device* device);
	virtual ID3D11Buffer* CreateMaterialBuffer(ID3D11Device* device);
	ID3D11Buffer* lightBuffer;
	ID3D11Buffer* materialBuffer;
};

