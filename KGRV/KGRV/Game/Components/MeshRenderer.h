#pragma once
#include "ObjectComponent.h"
class ObjectComponent;
class MeshRenderer : public ObjectComponent {
	void Draw() override;
	void Update(float deltaTime) override;
	MeshRenderer(GameObject gameObject*):
};