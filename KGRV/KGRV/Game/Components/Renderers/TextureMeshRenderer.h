#pragma once
#include "MeshRenderer.h"
#include "../../Graphics/Shaders/TextureShader.h"
class TextureMeshRenderer : public MeshRenderer
{
public:
	TextureMeshRenderer(GameObject* gameObject, Mesh* renderedMesh, TextureShader* drawShader) :MeshRenderer(gameObject, renderedMesh, drawShader) {

	}
protected:
	void DrawObject(ID3D11DeviceContext* context, ID3D11RenderTargetView* targetView, ID3D11DepthStencilState* depthState) override;

};

