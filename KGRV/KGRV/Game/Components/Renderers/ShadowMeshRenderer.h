#pragma once
#include "LightedTextureMeshRenderer.h"
#include "../../Graphics/Shaders/ShadowShader.h"
class ShadowMeshRenderer :
    public LightedTextureMeshRenderer
{

public:
    ShadowMeshRenderer(GameObject* gameObject, Mesh* renderedMesh, ShadowShader* drawShader) :LightedTextureMeshRenderer(gameObject, renderedMesh, drawShader) {

    }
    ID3D11Buffer* CreateTransformBuffer(ID3D11Device* device) override;

protected:
    void UpdateDrawMatrix() override;
    void UpdateLightBuffer() override;
    ID3D11Buffer* CreateLightBuffer(ID3D11Device* device) override;
};

