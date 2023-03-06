#include "RotateAroundComponent.h"
#include "..\3rdParty\SimpleMath.h"
void RotateAroundComponent::Update(float deltaTime)
{
    auto targetObjectPos = targetObject->transform->position;
    storedRotation += deltaTime * speed;
    Vector3 targetVector = rotVector;
    auto rot = Matrix::CreateFromAxisAngle(rotAxis, storedRotation);
    targetVector = Vector3::Transform(targetVector, rot);

    gameObject->transform->position = targetObjectPos + targetVector;

//    gameObject->transform->position.x = targetObject->transform->position.x + targetVector.x;
//    gameObject->transform->position.y = targetObject->transform->position.y + targetVector.y;
//    gameObject->transform->position.z = targetObject->transform->position.z + targetVector.z;
}

bool RotateAroundComponent::Initialization()
{
    return false;
}
