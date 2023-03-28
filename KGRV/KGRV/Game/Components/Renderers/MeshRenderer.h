#pragma once
#include "../ObjectComponent.h"
class ObjectComponent;
class MeshRenderer : public ObjectComponent {
public:
	void Draw() override;
	void Update(float deltaTime) override;
	virtual ID3D11Buffer* CreateTransformBuffer(ID3D11Device* device);
	virtual bool Initialization() override;
	MeshRenderer(GameObject* gameObject, Mesh* renderedMesh, Shader* drawShader) :ObjectComponent(gameObject) {
		this->renderedMesh = renderedMesh;
		this->drawShader = drawShader;
	}
protected:
	void UpdateDrawMatrix();
	virtual void InitBuffers(ID3D11Device* device);
	virtual void UpdateConstantBuffers();
	virtual void DrawObject(ID3D11DeviceContext* context, ID3D11RenderTargetView* targetView, ID3D11DepthStencilState* depthState);
	
	Mesh* renderedMesh;
	Shader* drawShader;
	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;
	ID3D11Buffer* transformBuffer;
	bool moved = true;
};