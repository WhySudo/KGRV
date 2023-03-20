#include "TextureMeshRenderer.h"
#include <iostream>

void TextureMeshRenderer::DrawObject(ID3D11DeviceContext* context, ID3D11RenderTargetView* targetView, ID3D11DepthStencilState* depthState)
{
	UINT strides[] = { sizeof(Vertex) };
	UINT offsets[] = { 0 };
	context->IASetInputLayout(drawShader->layout);
	context->IASetPrimitiveTopology(renderedMesh->topology);
	context->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	context->IASetVertexBuffers(0, 1, &vertexBuffer, strides, offsets);
	context->VSSetShader(drawShader->vertexShader, nullptr, 0);
	context->OMSetDepthStencilState(depthState, 0);

	
	if (renderedMesh->assignedTexture != nullptr) {
		auto tex = renderedMesh->assignedTexture;
		context->PSSetSamplers(0, 1, &tex->samplerState);
		context->PSSetShaderResources(0, 1, &tex->textureResourceView);
	}
	context->PSSetShader(drawShader->pixelShader, nullptr, 0);

	context->VSSetConstantBuffers(0, 1, &transformBuffer);

	context->DrawIndexed(renderedMesh->indecesCount, 0, 0);
}

