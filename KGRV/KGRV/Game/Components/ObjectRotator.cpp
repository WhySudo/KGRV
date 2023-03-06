#include "ObjectRotator.h"

void ObjectRotator::Update(float deltaTime)
{
	gameObject->transform->rotation.y += zRotationSpeed * deltaTime;

}

bool ObjectRotator::Initialization()
{
	return false;
}
