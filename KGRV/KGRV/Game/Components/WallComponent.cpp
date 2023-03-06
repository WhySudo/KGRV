#include "WallComponent.h"

void WallComponent::Update(float deltaTime)
{
    DirectX::XMFLOAT3 pos = { gameObject->transform->position.x, gameObject->transform->position.y, gameObject->transform->position.z };
    boundingBox->Center = pos;
}

bool WallComponent::Initialization()
{
    return false;
}
